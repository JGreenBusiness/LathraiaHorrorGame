// Fill out your copyright notice in the Description page of Project Settings.


#include "PanicManagerComponent.h"
#include "Math/UnrealMathUtility.h"


UPanicManagerComponent::UPanicManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UPanicManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

float UPanicManagerComponent::LerpPanicMeter(float DeltaTime)
{
	if (Panicking)
	{
		return PanicMeter = FMath::Lerp(PanicMeter,MaxPanic,PositivePanicRate);
	}
	else
	{
		return PanicMeter = FMath::Lerp(PanicMeter, 0, NegativePanicRate);
	}
}


void UPanicManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Green, FString::Printf(TEXT("Panic = %f%%"), PanicMeter));
	}

}

