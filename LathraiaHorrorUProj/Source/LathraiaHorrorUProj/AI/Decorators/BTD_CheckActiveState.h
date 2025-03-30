// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_CheckActiveState.generated.h"

/**
 * CheckActiveState decorator.
 * Checks the active state of the EyeStalk.
 */
UCLASS()
class LATHRAIAHORRORUPROJ_API UBTD_CheckActiveState : public UBTDecorator
{
	GENERATED_BODY()

	UBTD_CheckActiveState();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
