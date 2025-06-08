// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EyeStalk.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_CheckEyeStalkMode.generated.h"

/**
 * CheckEyeStalkMode Decorator.
 * Checks if the EyeStalk's current mode is equal to CheckMode.
 */
UCLASS()
class LATHRAIAHORRORUPROJ_API UBTD_CheckEyeStalkMode : public UBTDecorator
{
	GENERATED_BODY()

	UBTD_CheckEyeStalkMode();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:
	UPROPERTY(EditAnywhere, Category = "Check Eye Stalk Mode")
	TEnumAsByte<EEyeStalkMode> CheckMode = ESM_Surveillance;
	
};
