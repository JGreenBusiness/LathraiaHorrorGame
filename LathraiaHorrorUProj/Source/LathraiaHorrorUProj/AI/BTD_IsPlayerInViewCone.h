// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_IsPlayerInViewCone.generated.h"

/**
 * IsPlayerInViewCone Decorator.
 * Checks if the player is in the EyeStalk's view cone.
 */
UCLASS()
class LATHRAIAHORRORUPROJ_API UBTD_IsPlayerInViewCone : public UBTDecorator
{
	GENERATED_BODY()

	UBTD_IsPlayerInViewCone();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	// In Degrees
	float AngleBetweenVectors(const FVector& A, const FVector& B) const;
	
};
