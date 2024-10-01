// Fill out your copyright notice in the Description page of Project Settings.


#include "EyeStalk.h"

#include "AIController.h"
#include "EnemyHelpers.h"
#include "ViewConeComponent.h"
#include "LHCharacter.h"
#include "MathHelpers.h"
#include "EyeStalkManager.h"

AEyeStalk::AEyeStalk()
{
	PrimaryActorTick.bCanEverTick = true;
	
 	AutoPossessPlayer = EAutoReceiveInput::Disabled;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>("Root Mesh");
	SetRootComponent(RootMesh);

	ViewCone = CreateDefaultSubobject<UViewConeComponent>("View Cone");
	ViewCone->SetupAttachment(RootMesh);
}

void AEyeStalk::BeginPlay()
{
	Super::BeginPlay();

	if (UEyeStalkManager* ESManager = GetWorld()->GetSubsystem<UEyeStalkManager>())
	{
		ESManager->RegisterEyeStalk(this);
	}
}

void AEyeStalk::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsActive)
	{
		switch (CurrentMode)
		{
			case ESM_Surveillance: Mode_Surveillance(DeltaSeconds); break;
			case ESM_SurveillanceEx: Mode_SurveillanceEx(DeltaSeconds); break;
			case ESM_Rem: Mode_Rem(DeltaSeconds); break;
			default: break;
		}

		SelectBehaviorTree();
	}
}

void AEyeStalk::SetEyeStalkMode(const EEyeStalkMode NewMode)
{
	if (NewMode == ESM_Rem) // when entering REM, store the 'YawToPlayer'
	{
		if (const ALHCharacter* PlayerCharacter = EnemyHelpers::GetPlayerFromWorld(GetWorld()))
		{
			const FVector ToPlayer = (PlayerCharacter->GetActorLocation() - GetActorLocation()).GetSafeNormal();
			YawToPlayer = FMath::RadiansToDegrees(ToPlayer.HeadingAngle());
		}
	}
	else if (NewMode == ESM_SurveillanceEx)
	{
		// De-activate EyeStalk
		SetEyeStalkActive(false);

		// Set-up timers
		FTimerManager& TimerManager = GetWorld()->GetTimerManager();
		TimerManager.SetTimer(RandomEyeStalkTimer, this, &AEyeStalk::Random_SurveillanceEx, RandomActivationInterval, true, 0.f);
		TimerManager.SetTimer(SurveillanceExTimer, this, &AEyeStalk::End_SurveillanceEx, TotalModeLength, false);
	}
		
	CurrentMode = NewMode;
}

void AEyeStalk::IncreaseAwarenessMeter()
{
	const ALHCharacter* PlayerCharacter = Cast<ALHCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!IsValid(PlayerCharacter))
	{
		return;
	}

	float Amount = 0.f;

	// -> Distance from eye
	const float DistanceFromEye = FVector::Distance(GetActorLocation(), PlayerCharacter->GetActorLocation());
	Amount += (1.f - MathHelpers::Clamp01(DistanceFromEye / ViewCone->Length)) * DistanceMultiplier;

	// -> Angle from center of view cone
	const FVector ToPlayer = (PlayerCharacter->GetActorLocation()- GetActorLocation()).GetSafeNormal();
	const float AngleFromCenter = MathHelpers::AngleBetweenVectors(GetActorForwardVector(), ToPlayer);
	Amount += (1.f - MathHelpers::Clamp01(AngleFromCenter / ViewCone->HalfAngle)) * AngleMultiplier;

	// -> Player stance (Standing or crouching)
	Amount *= (PlayerCharacter->bIsCrouched ? CrouchMultiplier : 1.f);

	// -> Player motion (moving or still)
	Amount *= (PlayerCharacter->GetVelocity().IsNearlyZero() ? MovingMultiplier : 1.f);

	// -> Lantern light level (higher light level = higher awareness)
	// Amount += PlayerCharacter->LanternLevel / PlayerCharacter->MaxLanternLevel;
	
	AwarenessMeter += Amount;
}

void AEyeStalk::SelectBehaviorTree()
{
	if (AAIController* AIController = Cast<AAIController>(Controller))
	{
		const UBehaviorTree* CurrentTree = GetCurrentTree(AIController);
		
		if (CurrentPhase == ESP_Aggro && CurrentTree != BehaviorTree_Aggro)
		{
			AIController->RunBehaviorTree(BehaviorTree_Aggro);
		}
		else if (CurrentPhase == ESP_Hunting && CurrentTree != BehaviorTree_Hunting)
		{
			AIController->RunBehaviorTree(BehaviorTree_Hunting);
		}
	}
}

UBehaviorTree* AEyeStalk::GetCurrentTree(const AAIController* AIController)
{
	UBehaviorTree* CurrentTree = nullptr;
	
	if (IsValid(AIController))
	{
		if (const UBehaviorTreeComponent* BehaviorComp = Cast<UBehaviorTreeComponent>(AIController->BrainComponent))
		{
			CurrentTree = BehaviorComp->GetCurrentTree();
		}
	}

	return CurrentTree;
}

void AEyeStalk::Mode_Surveillance(const float DeltaSeconds)
{
	SwingEye(SwingSpeed_Surveillance * DeltaSeconds, SwingAngleMin_Surveillance, SwingAngleMax_Surveillance);
}

void AEyeStalk::Mode_Rem(const float DeltaSeconds)
{
	SwingEye(SwingSpeed_REM * DeltaSeconds, YawToPlayer + SwingAngleMin_REM, YawToPlayer + SwingAngleMax_REM);
}

void AEyeStalk::Mode_SurveillanceEx(const float DeltaSeconds)
{
	// TODO - implement SurveillanceEx logic
}

void AEyeStalk::Random_SurveillanceEx()
{
	// De-activate last random EyeStalk
	if (IsValid(LastRandomEyeStalk))
	{
		LastRandomEyeStalk->SetEyeStalkActive(false);
	}

	// Activate random EyeStalk
	if (UEyeStalkManager* ESManager = GetWorld()->GetSubsystem<UEyeStalkManager>())
	{
		LastRandomEyeStalk = ESManager->ActivateRandomEyeStalk({ this, LastRandomEyeStalk });
	}
}

void AEyeStalk::End_SurveillanceEx()
{
	// De-activate last activated EyeStalk
	if (IsValid(LastRandomEyeStalk))
	{
		LastRandomEyeStalk->SetEyeStalkActive(false);
	}
	LastRandomEyeStalk = nullptr;

	// Stop the timers
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	TimerManager.ClearTimer(RandomEyeStalkTimer);
	TimerManager.ClearTimer(SurveillanceExTimer);

	// Re-activate us
	SetEyeStalkActive(true);
	SetEyeStalkMode(ESM_Surveillance);
}

void AEyeStalk::SwingEye(const float SwingSpeed, const float MinimumAngle, const float MaximumAngle)
{
	// Rotate Yaw between min. and max. angle, flipping direction when outside extents
	
	FRotator Rotation = GetActorRotation();

	if (SwingDirection && Rotation.Yaw >= MaximumAngle) // Check for max angle
	{
		SwingDirection = false;
	}
	else if (!SwingDirection && Rotation.Yaw <= MinimumAngle) // Check for min angle
	{
		SwingDirection = true;
	}

	Rotation.Yaw += SwingSpeed * (SwingDirection ? 1.f : -1.f);
	
	SetActorRotation(Rotation);
}

#if WITH_EDITOR
void AEyeStalk::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property == nullptr)
	{
		return;
	}

	const FName PropertyName = PropertyChangedEvent.Property->NamePrivate;

	if (SwingAngleMin_Surveillance > SwingAngleMax_Surveillance && PropertyName == "SwingAngleMax_Surveillance")
	{
		SwingAngleMin_Surveillance = SwingAngleMax_Surveillance;
	}

	if (SwingAngleMax_Surveillance < SwingAngleMin_Surveillance && PropertyName == "SwingAngleMin_Surveillance")
	{
		SwingAngleMax_Surveillance = SwingAngleMin_Surveillance;
	}

	if (SwingAngleMin_REM > SwingAngleMax_REM && PropertyName == "SwingAngleMax_REM")
	{
		SwingAngleMin_REM = SwingAngleMax_REM;
	}

	if (SwingAngleMax_REM < SwingAngleMin_REM && PropertyName == "SwingAngleMin_REM")
	{
		SwingAngleMax_REM = SwingAngleMin_REM;
	}
}
#endif
