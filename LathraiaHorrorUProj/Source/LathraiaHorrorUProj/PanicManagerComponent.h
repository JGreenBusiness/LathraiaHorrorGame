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
	void UpdateMassPanicReductionFlag();
	void StartOutOfLineOfSightDelay();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float PanicMeter = 0.0f;

	float MaxPanic = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsPanicking = true;

	bool bWasInLineOfSight = false;

	TArray<float> PanicTierThresholdArray;
	int CurrentPanicTier = 0;

	FTimerHandle MassPanicReductionTimer;

public:	
	// Panic Tiers

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

	UPROPERTY(BlueprintAssignable, Category = "Panic")
	FOnPanicTierDelegate OnMaxPanicTier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panic Manager Config")
	TArray<FPanicTierData> PanicTierData;

	// Panic Rates

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panic Manager Config")
	float DefaultPositivePanicRate = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panic Manager Config")
	float SeenPositivePanicRate = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panic Manager Config")
	float NegativePanicRate = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panic Manager Config")
	int PanicReductionTier = 3;
	//

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsInLineOfSight = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsMassPanicReductionEnabled = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panic Manager Config")
	float MassPanicReductionDelay = 10.0f;
	
public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetPanicking(bool IsPanicking) { bIsPanicking = IsPanicking; }
	void DecreasePanic(float ValueToDecreasePanicBy);

	float GetPanicMeter() { return PanicMeter; }

	const int GetCurrentPanicTier() const { return CurrentPanicTier; }
};
