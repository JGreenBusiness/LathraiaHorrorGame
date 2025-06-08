// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EyeStalk.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_SwitchPhase.generated.h"

/**
 * SwitchPhase task node.
 * Switches the EyeStalk's current phase to NewPhase.
 */
UCLASS()
class LATHRAIAHORRORUPROJ_API UBTT_SwitchPhase : public UBTTaskNode
{
	GENERATED_BODY()
	
	UBTT_SwitchPhase();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Switch Phase")
	TEnumAsByte<EEyeStalkPhase> NewPhase = ESP_Hunting;
	
};
