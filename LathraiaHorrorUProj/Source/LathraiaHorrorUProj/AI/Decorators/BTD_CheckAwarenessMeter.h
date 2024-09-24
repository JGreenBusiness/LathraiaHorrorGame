// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_CheckAwarenessMeter.generated.h"

/**
 * CheckAwarenessMeter decorator.
 * Checks if the EyeStalk's awareness meter is full.
 */
UCLASS()
class LATHRAIAHORRORUPROJ_API UBTD_CheckAwarenessMeter : public UBTDecorator
{
	GENERATED_BODY()

	UBTD_CheckAwarenessMeter();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:
	UPROPERTY(EditAnywhere, Category = "Check Awareness Meter")
	float AwarenessMeterMax = 100.f;
	
};
