// Fill out your copyright notice in the Description page of Project Settings.


#include "EyeStalk.h"

#include "AIController.h"
#include "EnemyHelpers.h"
#include "ViewConeComponent.h"
#include "LHCharacter.h"
#include "MathHelpers.h"

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

void AEyeStalk::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	switch (CurrentMode)
	{
		case ESM_Surveillance: Mode_Surveillance(DeltaSeconds); break;
		case ESM_SurveillanceEx: Mode_SurveillanceEx(DeltaSeconds); break;
		case ESM_Rem: Mode_Rem(DeltaSeconds); break;
		default: break;
	}

	SelectBehaviorTree();
}

void AEyeStalk::SetEyeStalkMode(const EEyeStalkMode NewMode)
{
	if (const ALHCharacter* PlayerCharacter = EnemyHelpers::GetPlayerFromWorld(GetWorld()))
	{
		const FVector ToPlayer = (PlayerCharacter->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		YawToPlayer = FMath::RadiansToDegrees(ToPlayer.HeadingAngle());
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
	SwingEye(10.f * DeltaSeconds, -60.f, 60.f);
}

void AEyeStalk::Mode_SurveillanceEx(const float DeltaSeconds)
{
	GEngine->AddOnScreenDebugMessage(0, 3, FColor::Green, "TODO - Implement SurveillanceEx");
}

void AEyeStalk::Mode_Rem(const float DeltaSeconds)
{
	SwingEye(20.f * DeltaSeconds, YawToPlayer - 30.f, YawToPlayer + 30.f);
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
