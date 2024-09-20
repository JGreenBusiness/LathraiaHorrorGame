// Fill out your copyright notice in the Description page of Project Settings.


#include "Lantern.h"
#include "Kismet/GameplayStatics.h"
#include "LHCharacter.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/PointLightComponent.h"

ALantern::ALantern()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComponent"));

	LanternMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LanternMesh"));
	LanternMeshComponent->SetupAttachment(RootComponent);

	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("LanternPointLight"));
	PointLightComponent->SetupAttachment(LanternMeshComponent);
	MaxLanternIntensity = PointLightComponent->Intensity;
}

void ALantern::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<ALHCharacter>( UGameplayStatics::GetPlayerCharacter(this, 0));
	USkeletalMeshComponent* playerMeshComponent = Player->GetMesh();

	LanternSockets.Add(ELanternState::ELS_Held, playerMeshComponent->GetSocketByName(HeldLanternSocketName));
	LanternSockets.Add(ELanternState::ELS_Stowed, playerMeshComponent->GetSocketByName(StowedLanternSocketName));
	LanternSockets.Add(ELanternState::ELS_RekindleReady, playerMeshComponent->GetSocketByName(RekindleLanternSocketName));
	LanternSockets.Add(ELanternState::ELS_InUse, playerMeshComponent->GetSocketByName(InUseLanternSocketName));

	if (bSpawnOnPlayer)
	{
		SetLanternState(DefaultLanternSocket);
	}
}

void ALantern::ChangeState(ELanternState NewLanternState)
{
	CurrentLanternState = NewLanternState;
	float intensityModifier = 0;
	switch (CurrentLanternState)
	{
	case ELanternState::ELS_Held:
		intensityModifier = HeldLightModifier;
		break;
	case ELanternState::ELS_Stowed:
		intensityModifier = StowedLightModifier;
		break;
	case ELanternState::ELS_RekindleReady:
		break;
	case ELanternState::ELS_InUse:
		intensityModifier = InUseLightModifier;
		break;
	default:
		break;
	}
	PointLightComponent->SetIntensity(MaxLanternIntensity * intensityModifier);

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
			ChangeState(NewLanternState);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Lantern.cpp: Could Not Attatch Lantern to Lantern Socket"));
	}
}

void ALantern::ToggleLanternHeldState()
{
	CurrentLanternState == ELanternState::ELS_Held?
		SetLanternState(ELanternState::ELS_Stowed):
		SetLanternState(ELanternState::ELS_Held);
}

