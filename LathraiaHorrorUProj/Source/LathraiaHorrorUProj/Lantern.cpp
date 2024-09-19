// Fill out your copyright notice in the Description page of Project Settings.


#include "Lantern.h"
#include "Kismet/GameplayStatics.h"
#include "LHCharacter.h"
#include "Engine/SkeletalMeshSocket.h"

ALantern::ALantern()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ALantern::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ALHCharacter>( UGameplayStatics::GetPlayerCharacter(this, 0));
	USkeletalMeshComponent* playerMeshComponent = Player->GetMesh();

	LanternSockets.Add(ELanternState::ELST_Held, playerMeshComponent->GetSocketByName(HeldLanternSocketName));
	LanternSockets.Add(ELanternState::ELST_Stowed, playerMeshComponent->GetSocketByName(StowedLanternSocketName));
	LanternSockets.Add(ELanternState::ELST_RekindleReady, playerMeshComponent->GetSocketByName(RekindleLanternSocketName));

	if (bSpawnOnPlayer)
	{
		SetLanternState(DefaultLanternSocket);
	}
}


void ALantern::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALantern::SetLanternState(ELanternState NewLanternState)
{
	if (!Player->HasLantern())
	{
		Player->SetLantern(this);
	}

	// Switches lantern state and attatches to mesh component if appropriate lantern socket is found 
	if (const USkeletalMeshSocket* LanternSocket = *LanternSockets.Find(NewLanternState))
	{
		if (AttachToComponent(Player->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, LanternSocket->SocketName))
		{
			ActiveLanternState = NewLanternState;
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Lantern.cpp: Could Not Attatch Lantern to Lantern Socket"));
	}
}

void ALantern::ToggleLanternHeldState()
{
	switch (ActiveLanternState)
	{
	case ELanternState::ELST_Held:
		SetLanternState(ELanternState::ELST_Stowed);
		break;
	case ELanternState::ELST_Stowed:
		SetLanternState(ELanternState::ELST_Held);
		break;
	case ELanternState::ELST_RekindleReady:
		SetLanternState(ELanternState::ELST_Held);
		break;
	default:
		break;
	}
}

