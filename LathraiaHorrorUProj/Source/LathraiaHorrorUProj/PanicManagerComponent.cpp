// Fill out your copyright notice in the Description page of Project Settings.


#include "PanicManagerComponent.h"
#include "Math/UnrealMathUtility.h"




UPanicManagerComponent::UPanicManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	PanicTierData.Add(FPanicTierData{ EPanicTier::EPT_Tier_1, 10.0f });
	PanicTierData.Add(FPanicTierData{ EPanicTier::EPT_Tier_2, 25.0f });
	PanicTierData.Add(FPanicTierData{ EPanicTier::EPT_Tier_3, 40.0f });
	PanicTierData.Add(FPanicTierData{ EPanicTier::EPT_Tier_4, 80.0f });
	PanicTierData.Add(FPanicTierData{ EPanicTier::EPT_Tier_5, 100.0f });

}


void UPanicManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UPanicManagerComponent::LerpPanicMeter(float DeltaTime)
{
	if (Panicking)
	{
		PanicMeter = FMath::FInterpConstantTo(PanicMeter, MaxPanic, DeltaTime, PositivePanicRate);
	}
	else
	{
		PanicMeter = FMath::FInterpConstantTo(PanicMeter, 0, DeltaTime, NegativePanicRate);
	}
}


void UPanicManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	LerpPanicMeter(DeltaTime);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Green, FString::Printf(TEXT("Panic = %f%%"), PanicMeter));
	}

}

