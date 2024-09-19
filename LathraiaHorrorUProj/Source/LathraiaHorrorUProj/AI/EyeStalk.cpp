// Fill out your copyright notice in the Description page of Project Settings.


#include "EyeStalk.h"

#include "AIController.h"
#include "ViewConeComponent.h"
#include "LathraiaHorrorUProj/LHCharacter.h"
#include "LathraiaHorrorUProj/MathHelpers.h"

AEyeStalk::AEyeStalk()
{
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

	if (AAIController* AIController = Cast<AAIController>(Controller))
	{
		AIController->RunBehaviorTree(BehaviorTree);
	}
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
