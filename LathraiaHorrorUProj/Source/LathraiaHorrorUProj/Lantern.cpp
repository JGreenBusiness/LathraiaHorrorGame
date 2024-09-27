// Fill out your copyright notice in the Description page of Project Settings.


#include "Lantern.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/PointLightComponent.h"
#include "Math/UnrealMathUtility.h"

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
}

void ALantern::AddLanternSocket(USkeletalMeshComponent* ActorMeshComponent, ELanternState LanternState, FName LanternSocketName)
{
	LanternSockets.Add(LanternState, ActorMeshComponent->GetSocketByName(LanternSocketName));
}

void ALantern::BeginPlay()
{
	Super::BeginPlay();
}

void ALantern::ChangeLanternState(ELanternState NewLanternState)
{
	CurrentLanternState = NewLanternState;
	FireIntensityTeirDestination = EFireIntensityTeir::EFT_Snuffed;
	switch (CurrentLanternState)
	{
	case ELanternState::ELS_Held:
		BurnRate = HeldBurnRate;
		break;
	case ELanternState::ELS_Stowed:
		BurnRate = StowedBurnRate;
		break;
	case ELanternState::ELS_RekindleReady:
		BurnRate = RekindlingBurnRate;
		FireIntensityTeirDestination = EFireIntensityTeir::EFT_TeirFive;
		break;
	case ELanternState::ELS_InUse:
		BurnRate = InUseBurnRate;
		break;
	default:
		break;
	}
}

float ALantern::LerpFlameIntensity(float DeltaTime)
{
	float lightIntesnsityDestination = MaxLanternIntensity * GetFireIntensityTeirRatio(FireIntensityTeirDestination);
	CurrentFlameIntensity = FMath::Lerp(CurrentFlameIntensity, lightIntesnsityDestination, BurnRate);

	if (CurrentLanternState != ELanternState::ELS_Stowed)
	{
		return CurrentFlameIntensity;
	}
	else
	{
		return CurrentFlameIntensity * StowedDimedRatio;
	}
}


void ALantern::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float newLightIntensity = LerpFlameIntensity(DeltaTime);
	PointLightComponent->SetIntensity(newLightIntensity);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Green, FString::Printf(TEXT("Flame = %f%%"), (newLightIntensity / MaxLanternIntensity)*100));
	}

}

void ALantern::SetLanternState(USceneComponent* MeshWithLanternSockets,ELanternState NewLanternState)
{
	// Switches lantern state and attatches to mesh component if appropriate lantern socket is found 
	if (const USkeletalMeshSocket* LanternSocket = *LanternSockets.Find(NewLanternState))
	{
		if (AttachToComponent(MeshWithLanternSockets, FAttachmentTransformRules::SnapToTargetNotIncludingScale, LanternSocket->SocketName))
		{
			ChangeLanternState(NewLanternState);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Lantern.cpp: Could Not Attatch Lantern to Lantern Socket"));
	}
}

void ALantern::ToggleLanternHeldState(USceneComponent* MeshWithLanternSockets)
{
	CurrentLanternState == ELanternState::ELS_Held?
		SetLanternState(MeshWithLanternSockets,ELanternState::ELS_Stowed):
		SetLanternState(MeshWithLanternSockets,ELanternState::ELS_Held);
}

