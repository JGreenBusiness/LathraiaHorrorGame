// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_SwitchMode.h"

#include "EnemyHelpers.h"

UBTT_SwitchMode::UBTT_SwitchMode()
{
	NodeName = "Switch Mode";
}

EBTNodeResult::Type UBTT_SwitchMode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AEyeStalk* EyeStalk = EnemyHelpers::GetEyeStalkFromBTComp(OwnerComp))
	{
		EyeStalk->SetEyeStalkMode(NewMode);
	}
	
	return EBTNodeResult::Succeeded;
}
