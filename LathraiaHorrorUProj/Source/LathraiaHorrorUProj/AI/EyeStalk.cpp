// Fill out your copyright notice in the Description page of Project Settings.


#include "EyeStalk.h"

#include "AIController.h"

AEyeStalk::AEyeStalk()
{
 	AutoPossessPlayer = EAutoReceiveInput::Disabled;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>("Root Mesh");
	SetRootComponent(RootMesh);
}

void AEyeStalk::BeginPlay()
{
	Super::BeginPlay();

	if (AAIController* AIController = Cast<AAIController>(Controller))
	{
		AIController->RunBehaviorTree(BehaviorTree);
	}
}
