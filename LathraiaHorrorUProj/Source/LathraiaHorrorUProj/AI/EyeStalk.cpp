// Fill out your copyright notice in the Description page of Project Settings.


#include "EyeStalk.h"

#include "AIController.h"
#include "ViewConeComponent.h"

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
