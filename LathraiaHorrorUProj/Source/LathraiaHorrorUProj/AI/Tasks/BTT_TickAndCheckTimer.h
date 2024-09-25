// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_TickAndCheckTimer.generated.h"

/**
 * TickAndCheckTimer task node.
 * Ticks a float blackboard key, and checks it against TimerMax.
 * Returns Succeeded or Failed based on TimerKey >= TimerMax.
 */
UCLASS()
class LATHRAIAHORRORUPROJ_API UBTT_TickAndCheckTimer : public UBTTaskNode
{
	GENERATED_BODY()

	UBTT_TickAndCheckTimer();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Tick And Check Timer") // What key to store the timer value in.
	FBlackboardKeySelector TimerKey;

	UPROPERTY(EditAnywhere, Category = "Tick And Check Timer")
	float TimerMax = 3.f;

	// MinValue is being used as the 'None' / 'Null' value
	FDateTime LastTime = FDateTime::MinValue();
	
};
