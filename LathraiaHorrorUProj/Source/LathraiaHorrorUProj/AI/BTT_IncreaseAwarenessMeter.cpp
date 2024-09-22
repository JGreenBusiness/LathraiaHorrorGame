// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_IncreaseAwarenessMeter.h"

#include "EnemyHelpers.h"
#include "EyeStalk.h"

UBTT_IncreaseAwarenessMeter::UBTT_IncreaseAwarenessMeter()
{
	NodeName = "Increase Awareness Meter";
}

EBTNodeResult::Type UBTT_IncreaseAwarenessMeter::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (AEyeStalk* EyeStalk = EnemyHelpers::GetEyeStalkFromBTComp(OwnerComp))
	{
		EyeStalk->IncreaseAwarenessMeter();
	}
	
	return EBTNodeResult::Succeeded;
}
