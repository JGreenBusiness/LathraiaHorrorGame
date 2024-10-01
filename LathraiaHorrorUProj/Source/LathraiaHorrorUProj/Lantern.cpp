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
		BurnRate = HeldBurnRate;
		break;
	case ELanternState::ELS_Rekindling:
		BurnRate = RekindlingBurnRate;
		FireIntensityTeirDestination = EFireIntensityTeir::EFT_TeirFive;
		break;
	case ELanternState::ELS_InUse:
		BurnRate = InUseBurnRate;
		break;
	default:
		break;
	}

	OnLanternNewLanternState();
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

		switch (CurrentLanternState)
		{
		case ELanternState::ELS_Held:
			GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Green, FString::Printf(TEXT("Current Lantern State: Held")));
			break;
		case ELanternState::ELS_Stowed:
			GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Green, FString::Printf(TEXT("Current Lantern State: Stowed")));
			break;
		case ELanternState::ELS_RekindleReady:
			GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Green, FString::Printf(TEXT("Current Lantern State: Rekindling : ready")));
			break;
		case ELanternState::ELS_Rekindling:
			GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Green, FString::Printf(TEXT("Current Lantern State: Rekindling : active")));
			break;
		case ELanternState::ELS_InUse:
			GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Green, FString::Printf(TEXT("Current Lantern State: In Use")));
			break;
		default:
			break;
		}
	}

}

void ALantern::SetLanternState(USceneComponent* MeshWithLanternSockets,ELanternState NewLanternState)
{

	if (const USkeletalMeshSocket* LanternSocket = *LanternSockets.Find(NewLanternState))
	{
		if (MeshWithLanternSockets->DoesSocketExist(LanternSocket->SocketName))
		{
			//AttachToComponent(MeshWithLanternSockets, FAttachmentTransformRules::KeepWorldTransform, LanternSocket->SocketName);
			ChangeLanternState(NewLanternState);
		}
	}

}

void ALantern::ToggleLanternHeldState(USceneComponent* MeshWithLanternSockets)
{
	CurrentLanternState == ELanternState::ELS_Held?
		SetLanternState(MeshWithLanternSockets,ELanternState::ELS_Stowed):
		SetLanternState(MeshWithLanternSockets,ELanternState::ELS_Held);
}

