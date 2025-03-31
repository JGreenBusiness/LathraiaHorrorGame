// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PanicManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPanicTierDelegate);


UENUM(BlueprintType)
enum class EPanicTier : uint8
{
	EPT_Tier_0 UMETA(DisplayName = "Panic Tier 0"),
	EPT_Tier_1 UMETA(DisplayName = "Panic Tier 1"),
	EPT_Tier_2 UMETA(DisplayName = "Panic Tier 2"),
	EPT_Tier_3 UMETA(DisplayName = "Panic Tier 3"),
	EPT_Tier_4 UMETA(DisplayName = "Panic Tier 4"),
	EPT_Tier_5 UMETA(DisplayName = "Panic Tier 5")
};

USTRUCT(BlueprintType)
struct FPanicTierData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Panic")
	EPanicTier Tier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panic")
	float Threshold;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LATHRAIAHORRORUPROJ_API UPanicManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPanicManagerComponent();

protected:
	virtual void BeginPlay() override;

	void LerpPanicMeter(float DeltaTime);
	void UpdateCurrentPanicTier();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float PanicMeter = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float MaxPanic = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool Panicking = true;

	TArray<float> PanicTierThresholdArray;
	int CurrentPanicTier = 0;

public:	

	UPROPERTY(BlueprintAssignable, Category = "Panic")
	FOnPanicTierDelegate OnPanicTierZero;

	UPROPERTY(BlueprintAssignable, Category = "Panic")
	FOnPanicTierDelegate OnPanicTierOne;

	UPROPERTY(BlueprintAssignable, Category = "Panic")
	FOnPanicTierDelegate OnPanicTierTwo;

	UPROPERTY(BlueprintAssignable, Category = "Panic")
	FOnPanicTierDelegate OnPanicTierThree;

	UPROPERTY(BlueprintAssignable, Category = "Panic")
	FOnPanicTierDelegate OnPanicTierFour;

	UPROPERTY(BlueprintAssignable, Category = "Panic")
	FOnPanicTierDelegate OnPanicTierFive;


public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetPanicking(bool IsPanicking) { Panicking = IsPanicking; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panic Manager Config")
	TArray<FPanicTierData> PanicTierData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panic Manager Config")
	float PositivePanicRate = .1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panic Manager Config")
	float NegativePanicRate = .1f;

};
