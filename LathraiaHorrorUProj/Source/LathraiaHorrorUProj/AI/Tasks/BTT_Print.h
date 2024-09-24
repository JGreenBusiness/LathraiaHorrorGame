// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_Print.generated.h"

/**
 * Print task node.
 * Prints a message as an OnScreenDebugMessage.
 */
UCLASS()
class LATHRAIAHORRORUPROJ_API UBTT_Print : public UBTTaskNode
{
	GENERATED_BODY()

	UBTT_Print();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, Category="Print")
	int32 Id = -1;

	UPROPERTY(EditAnywhere, Category="Print")
	float Duration = 3.f;

	UPROPERTY(EditAnywhere, Category="Print")
	FColor Color = FColor::Green;
	
	UPROPERTY(EditAnywhere, Category="Print")
	FString Message = "Hello World!";
};
