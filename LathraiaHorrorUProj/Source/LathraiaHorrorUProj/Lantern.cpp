// Fill out your copyright notice in the Description page of Project Settings.


#include "Lantern.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Components/PointLightComponent.h"
#include "Math/UnrealMathUtility.h"
#include "InteractionComponent.h"
#include "PanicManagerComponent.h"

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

	FTimerHandle RekindleDelayTimer;
	FTimerDelegate RekindleTimerDelegate;

	FTimerDelegate RelightTimerDelegate;
	FTimerHandle RelightDelayTimer;

	switch (CurrentLanternState)
	{
	case ELanternState::ELS_ReLighting:
		RelightTimerDelegate.BindUFunction(this, "ChangeLanternState", (ELanternState)ELanternState::ELS_Stowed);
		GetWorld()->GetTimerManager().SetTimer(RelightDelayTimer, RelightTimerDelegate, RelightLanternDelay, false);
		PanicManagerComponent->SetPanicking(true);
		break;
	case ELanternState::ELS_Rekindling:
		RekindleTimerDelegate.BindUFunction(this, "ChangeLanternState", (ELanternState)ELanternState::ELS_InUse);
		GetWorld()->GetTimerManager().SetTimer(RekindleDelayTimer, RekindleTimerDelegate, RekindlingDelay, false);
		break;
	case ELanternState::ELS_InUse:
		BurnRate = HeldBurnRate;
		PanicManagerComponent->SetPanicking(false);
		break;
	case ELanternState::ELS_Stowed:
		BurnRate = RekindlingBurnRate;
		PanicManagerComponent->SetPanicking(true);
		break;
	default:
		break;
	}

	OnLanternNewLanternState();
}

float ALantern::LerpFlameIntensity(float DeltaTime)
{


	switch (CurrentLanternState)
	{
	case ELanternState::ELS_InUse:

		if (CurrentFlameIntensity <= 0)
		{
			ChangeLanternState(ELanternState::ELS_ReLighting);
			return CurrentFlameIntensity;
		}

		return CurrentFlameIntensity = FMath::FInterpConstantTo(CurrentFlameIntensity, 0, DeltaTime, BurnRate);
		break;
	case ELanternState::ELS_Stowed:
		CurrentFlameIntensity = FMath::FInterpConstantTo(CurrentFlameIntensity, MaxLanternIntensity, DeltaTime, BurnRate);
		return CurrentFlameIntensity * StowedDimedRatio;
		break;
	case ELanternState::ELS_Rekindling:
		return CurrentFlameIntensity * StowedDimedRatio;
		break;
	case ELanternState::ELS_ReLighting:
		return CurrentFlameIntensity;
		break;
	default:
		return 0;
		break;
	}


}

void ALantern::OnInteraction()
{
	InteractionComponent->RemoveInteractionComponent();
}


void ALantern::InitializeLantern(USkeletalMeshComponent* LanternSocketedMesh, UPanicManagerComponent* PanicManager)
{
	MeshWithLanternSockets = LanternSocketedMesh;
	PanicManagerComponent = PanicManager;
}

void ALantern::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float oldLightIntensity = CurrentFlameIntensity;
	float newLightIntensity = LerpFlameIntensity(DeltaTime);
	PointLightComponent->SetIntensity(newLightIntensity);

	if (newLightIntensity == 0 && oldLightIntensity != newLightIntensity)
	{
		PanicManagerComponent->SetPanicking(true);
	}

	if (bDebugModeOn && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Green, FString::Printf(TEXT("Flame = %f%%"), (CurrentFlameIntensity / MaxLanternIntensity)*100));

		switch (CurrentLanternState)
		{
		case ELanternState::ELS_InUse:
			GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Green, FString::Printf(TEXT("Current Lantern State: In Use")));
			break;
		case ELanternState::ELS_Stowed:
			GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Green, FString::Printf(TEXT("Current Lantern State: Stowed")));
			break;
		case ELanternState::ELS_Rekindling:
			GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Green, FString::Printf(TEXT("Current Lantern State: Rekindling")));
			break;
		case ELanternState::ELS_ReLighting:
			GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Green, FString::Printf(TEXT("Current Lantern State: Relighting")));
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

const USkeletalMeshSocket* ALantern::GetActiveLanternSocket()
{
	const USkeletalMeshSocket* ActiveLanternSocket = *LanternSockets.Find(CurrentLanternState);
	if (IsValid(ActiveLanternSocket))
	{
		return ActiveLanternSocket;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Lantern.cpp: Could not GetActiveLanternSocket. Maybe Socket was not added "));
		return ActiveLanternSocket = *LanternSockets.Find(ELanternState::ELS_Stowed);
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
		AttachToComponent(MeshWithLanternSockets, FAttachmentTransformRules::KeepWorldTransform, GetActiveLanternSocket()->SocketName);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Lantern.cpp: MeshWithLanternSockets is a nullptr"));
	}
}

void ALantern::ToggleLanternHeldState()
{
	switch (CurrentLanternState)
	{
	case ELanternState::ELS_InUse:
		SetLanternState(ELanternState::ELS_Stowed);
		break;
	case ELanternState::ELS_Stowed:
		SetLanternState(ELanternState::ELS_Rekindling);
		break;
	default:
		break;
	}
}

