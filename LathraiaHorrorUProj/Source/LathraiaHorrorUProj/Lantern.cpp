// Fill out your copyright notice in the Description page of Project Settings.


#include "Lantern.h"
#include "Kismet/GameplayStatics.h"
#include "LHCharacter.h"
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
			ChangeLanternState(NewLanternState);
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

