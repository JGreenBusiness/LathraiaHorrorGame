// Fill out your copyright notice in the Description page of Project Settings.


#include "SpectralEye.h"

#include "EyeStalk.h"
#include "EnemyHelpers.h"
#include "Kismet/GameplayStatics.h"

ASpectralEye::ASpectralEye()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpectralEye::BeginPlay()
{
	Super::BeginPlay();

	if (ALHCharacter* Player = EnemyHelpers::GetPlayerFromWorld(GetWorld()))
	{
		Player->OnInteract.AddDynamic(this, &ASpectralEye::DispellEye);
	}
}

void ASpectralEye::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	KillMeter += DeltaTime;

	if (KillMeter >= KillMeterMax)
	{
		SpectralSwallow();
	}
}

void ASpectralEye::DispellEye()
{
	if (IsValid(StalkOwner))
	{
		StalkOwner->Reset();
		StalkOwner = nullptr;

		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, "TODO - Stun Eye Stalk");

		Destroy();
	}
}

void ASpectralEye::SpectralSwallow()
{
	UGameplayStatics::OpenLevel(GetWorld(), *GetWorld()->GetName(), false);

	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, "TODO - Spectral Swallow");
}

