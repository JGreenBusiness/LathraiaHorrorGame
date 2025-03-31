// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PanicManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LATHRAIAHORRORUPROJ_API UPanicManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPanicManagerComponent();

protected:
	virtual void BeginPlay() override;

	float LerpPanicMeter(float DeltaTime);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float PanicMeter = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float MaxPanic = 100.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool Panicking = true;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panic Manager Config")
	float PositivePanicRate = .1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Panic Manager Config")
	float NegativePanicRate = .1f;

	void SetPanicking(bool IsPanicking) { Panicking = IsPanicking; }
};
