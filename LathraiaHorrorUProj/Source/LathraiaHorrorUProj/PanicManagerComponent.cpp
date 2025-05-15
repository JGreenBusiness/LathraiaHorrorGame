// Fill out your copyright notice in the Description page of Project Settings.


#include "PanicManagerComponent.h"
#include "Math/UnrealMathUtility.h"




UPanicManagerComponent::UPanicManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Sets Panic Tier Threshold Defaults
	PanicTierData.Add(FPanicTierData{ EPanicTier::EPT_Tier_0, 0.0f });
	PanicTierData.Add(FPanicTierData{ EPanicTier::EPT_Tier_1, 10.0f });
	PanicTierData.Add(FPanicTierData{ EPanicTier::EPT_Tier_2, 25.0f });
	PanicTierData.Add(FPanicTierData{ EPanicTier::EPT_Tier_3, 40.0f });
	PanicTierData.Add(FPanicTierData{ EPanicTier::EPT_Tier_4, 80.0f });
	PanicTierData.Add(FPanicTierData{ EPanicTier::EPT_Tier_5, 100.0f });
}


void UPanicManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	for (FPanicTierData PanicData : PanicTierData)
	{
		float PanicThreshold = PanicData.Threshold;
		PanicTierThresholdArray.Add(PanicThreshold);
		if (PanicThreshold > MaxPanic)
		{
			MaxPanic = PanicThreshold;
		}
	}
}

void UPanicManagerComponent::LerpPanicMeter(float DeltaTime)
{
	if (bIsInLineOfSight)
	{
		PanicMeter = FMath::FInterpConstantTo(PanicMeter, MaxPanic, DeltaTime, SeenPositivePanicRate);
		bIsMassPanicReductionEnabled = false;
		if (!bWasInLineOfSight)
		{
			bWasInLineOfSight = true;
		}
	}
	else if (bIsPanicking)
	{
		PanicMeter = FMath::FInterpConstantTo(PanicMeter, MaxPanic, DeltaTime, DefaultPositivePanicRate);

		StartOutOfLineOfSightDelay();
	}
	else
	{
		PanicMeter = FMath::FInterpConstantTo(PanicMeter, 0, DeltaTime, NegativePanicRate);

		StartOutOfLineOfSightDelay();
	}
}

void UPanicManagerComponent::UpdateCurrentPanicTier()
{
	if (PanicMeter >= MaxPanic)
	{
		OnMaxPanicTier.Broadcast();
	}

	int newTier = 0;

	for (int i = 0; i < PanicTierThresholdArray.Num(); ++i)
	{
		if (PanicMeter < PanicTierThresholdArray[i])
		{
			newTier = i;
			break;
		}
	}

	if (CurrentPanicTier != newTier )
	{
		CurrentPanicTier = newTier;


		switch (CurrentPanicTier)
		{
		case 0:
			OnPanicTierZero.Broadcast();
			break;
		case 1:
			OnPanicTierOne.Broadcast();
			break;
		case 2:
			OnPanicTierTwo.Broadcast();
			break;
		case 3:
			OnPanicTierThree.Broadcast();
			break;
		case 4:
			OnPanicTierFour.Broadcast();
			break;
		case 5:
			OnPanicTierFive.Broadcast();
			break;
		default:
			break;
		}
	}

	if (CurrentPanicTier < PanicReductionTier)
	{
		bIsMassPanicReductionEnabled = false;
	}

}

void UPanicManagerComponent::UpdateMassPanicReductionFlag()
{
	if (!bIsInLineOfSight && CurrentPanicTier > PanicReductionTier)
	{
		bIsMassPanicReductionEnabled = true;
	}
}

void UPanicManagerComponent::StartOutOfLineOfSightDelay()
{
	if (bWasInLineOfSight)
	{
		bWasInLineOfSight = false;
		GetWorld()->GetTimerManager().SetTimer(MassPanicReductionTimer, this, &UPanicManagerComponent::UpdateMassPanicReductionFlag, MassPanicReductionDelay, false);
	}
	else if(GetWorld()->GetTimerManager().GetTimerRemaining(MassPanicReductionTimer) <= 0 && !bIsMassPanicReductionEnabled)
	{
		UpdateMassPanicReductionFlag();
	}
}


void UPanicManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateCurrentPanicTier();
	LerpPanicMeter(DeltaTime);
}

bool UPanicManagerComponent::DecreasePanic(float ValueToDecreasePanicBy)
{
	if (bIsMassPanicReductionEnabled)
	{
		bIsMassPanicReductionEnabled = false;
		PanicMeter -= ValueToDecreasePanicBy;
		if (PanicMeter < 0)
		{
			PanicMeter = 0;
		}
		UpdateCurrentPanicTier();
		return true;
	}

	return false;
}
