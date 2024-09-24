// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_IncreaseAwarenessMeter.generated.h"

/**
 * IncreaseAwarenessMeter task node.
 * Increases the EyeStalk's awareness meter.
 */
UCLASS()
class LATHRAIAHORRORUPROJ_API UBTT_IncreaseAwarenessMeter : public UBTTaskNode
{
	GENERATED_BODY()

	UBTT_IncreaseAwarenessMeter();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
