// Fill out your copyright notice in the Description page of Project Settings.


#include "Lantern.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/PointLightComponent.h"
#include "Math/UnrealMathUtility.h"
#include "InteractionComponent.h"

ALantern::ALantern()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComponent"));

	LanternMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LanternMesh"));
	LanternMeshComponent->SetupAttachment(RootComponent);

	PointLightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("LanternPointLight"));
	PointLightComponent->SetupAttachment(LanternMeshComponent);
	CurrentFlameIntensity = PointLightComponent->Intensity;
	MaxLanternIntensity = CurrentFlameIntensity;

	InteractionComponent = CreateDefaultSubobject<UInteractionComponent>(TEXT("InteractionComponent"));
}

void ALantern::AddLanternSocket(ELanternState LanternState, FName LanternSocketName)
{
	LanternSockets.Add(LanternState, MeshWithLanternSockets->GetSocketByName(LanternSocketName));
}

void ALantern::BeginPlay()
{
	Super::BeginPlay();

	if (InteractionComponent)
	{
		InteractionComponent->OnInteracted.AddDynamic(this, &ALantern::OnInteraction);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Lantern.cpp: Interaction Component is nullptr"));
	}
}

void ALantern::ChangeLanternState(ELanternState NewLanternState)
{
	CurrentLanternState = NewLanternState;
	switch (CurrentLanternState)
	{
	case ELanternState::ELS_Held:
		BurnRate = HeldBurnRate;
		break;
	case ELanternState::ELS_Stowed:
		BurnRate = RekindlingBurnRate;
		break;
	default:
		break;
	}

	OnLanternNewLanternState();
}

float ALantern::LerpFlameIntensity(float DeltaTime)
{
	if (CurrentLanternState == ELanternState::ELS_Held)
	{
		return CurrentFlameIntensity = FMath::Lerp(CurrentFlameIntensity, 0, BurnRate);
	}
	else
	{
		CurrentFlameIntensity = FMath::Lerp(CurrentFlameIntensity, MaxLanternIntensity, BurnRate) ;
		return CurrentFlameIntensity * StowedDimedRatio;
	}

}

void ALantern::OnInteraction()
{
	InteractionComponent->RemoveInteractionComponent();
}


void ALantern::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float newLightIntensity = LerpFlameIntensity(DeltaTime);
	PointLightComponent->SetIntensity(newLightIntensity);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Green, FString::Printf(TEXT("Flame = %f%%"), (newLightIntensity / MaxLanternIntensity)*100));

		switch (CurrentLanternState)
		{
		case ELanternState::ELS_Held:
			GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Green, FString::Printf(TEXT("Current Lantern State: Held")));
			break;
		case ELanternState::ELS_Stowed:
			GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Green, FString::Printf(TEXT("Current Lantern State: Stowed")));
			break;
		default:
			break;
		}
	}

}

void ALantern::SetLanternState(ELanternState NewLanternState)
{
	if (const USkeletalMeshSocket* LanternSocket = *LanternSockets.Find(NewLanternState))
	{
		if (MeshWithLanternSockets->DoesSocketExist(LanternSocket->SocketName))
		{
			ChangeLanternState(NewLanternState);
		}
	}
	
}

USkeletalMeshComponent* ALantern::GetMeshWithLanternSockets()
{
	if (MeshWithLanternSockets)
	{
		return MeshWithLanternSockets;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Lantern.cpp: MeshWithLanternSockets is a nullptr"));
	}
	return nullptr;
}

void ALantern::AttatchLanternToActiveSocket()
{
	if (MeshWithLanternSockets)
	{
		AttachToComponent(MeshWithLanternSockets, FAttachmentTransformRules::SnapToTargetNotIncludingScale, GetActiveLanternSocket()->SocketName);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Lantern.cpp: MeshWithLanternSockets is a nullptr"));
	}
}

void ALantern::ToggleLanternHeldState()
{
	CurrentLanternState == ELanternState::ELS_Held?
		SetLanternState(ELanternState::ELS_Stowed):
		SetLanternState(ELanternState::ELS_Held);
}

