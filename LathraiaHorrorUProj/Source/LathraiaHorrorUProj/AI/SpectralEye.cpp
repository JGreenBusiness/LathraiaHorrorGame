// Fill out your copyright notice in the Description page of Project Settings.


#include "SpectralEye.h"

#include "EyeStalk.h"

ASpectralEye::ASpectralEye()
{
	PrimaryActorTick.bCanEverTick = true;
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
		StalkOwner->SetEyeStalkActive(true);
		StalkOwner->SetEyeStalkPhase(ESP_Hunting);
		StalkOwner->SetEyeStalkMode(ESM_Surveillance);
		StalkOwner = nullptr;

		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, "TODO - Stun Eye Stalk");
	}
}

void ASpectralEye::SpectralSwallow()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, "TODO - Spectral Swallow");
}

