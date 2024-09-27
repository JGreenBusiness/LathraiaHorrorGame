// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EyeStalk.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_SwitchMode.generated.h"

/**
 * SwitchMode task node.
 * Switches the EyeStalk's current mode to NewMode.
 */
UCLASS()
class LATHRAIAHORRORUPROJ_API UBTT_SwitchMode : public UBTTaskNode
{
	GENERATED_BODY()

	UBTT_SwitchMode();
	
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, Category = "Switch Mode")
	TEnumAsByte<EEyeStalkMode> NewMode = ESM_Surveillance;
	
};
