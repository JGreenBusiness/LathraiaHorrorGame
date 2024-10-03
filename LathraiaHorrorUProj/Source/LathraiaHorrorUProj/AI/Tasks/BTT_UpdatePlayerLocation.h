// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_UpdatePlayerLocation.generated.h"

/**
 * UpdatePlayerLocation task node.
 * Stores the player's location in a vector blackboard key.
 */
UCLASS()
class LATHRAIAHORRORUPROJ_API UBTT_UpdatePlayerLocation : public UBTTaskNode
{
	GENERATED_BODY()

	UBTT_UpdatePlayerLocation();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	// Blackboard key to store the player location in.
	UPROPERTY(EditAnywhere, Category = "Move To Eye Nest")
	FBlackboardKeySelector PlayerLocationKey;
	
};
