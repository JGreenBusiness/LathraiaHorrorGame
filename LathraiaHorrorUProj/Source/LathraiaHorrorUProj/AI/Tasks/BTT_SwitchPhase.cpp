// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_SwitchPhase.h"

#include "EnemyHelpers.h"

UBTT_SwitchPhase::UBTT_SwitchPhase()
{
    NodeName = "Switch Phase";
}

EBTNodeResult::Type UBTT_SwitchPhase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    if (AEyeStalk* EyeStalk = EnemyHelpers::GetEyeStalkFromBTComp(OwnerComp))
    {
        EyeStalk->SetEyeStalkPhase(NewPhase);
    }

    return EBTNodeResult::Succeeded;
}
