// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpectralEye.generated.h"

class AEyeStalk;

UCLASS()
class LATHRAIAHORRORUPROJ_API ASpectralEye : public AActor
{
	GENERATED_BODY()
	
public:
	ASpectralEye();

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	void SetOwningEyeStalk(AEyeStalk* OwningEyeStalk) { StalkOwner = OwningEyeStalk; }

	UFUNCTION()
	void DispellEye();
	
protected:
	void SpectralSwallow();

protected:
	// In seconds
	UPROPERTY(VisibleAnywhere, Category = "Spectral Eye Config: General")
	float KillMeter = 0.f;

	// In seconds
	UPROPERTY(EditAnywhere, Category = "Spectral Eye Config: General", meta=(ClampMin=0.f))
	float KillMeterMax = 3.f;

	UPROPERTY()
	AEyeStalk* StalkOwner = nullptr;

};
