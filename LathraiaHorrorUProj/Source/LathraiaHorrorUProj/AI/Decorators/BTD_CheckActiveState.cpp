// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_CheckActiveState.h"

#include "EnemyHelpers.h"
#include "EyeStalk.h"

UBTD_CheckActiveState::UBTD_CheckActiveState()
{
	NodeName = "Check Active State";
}

bool UBTD_CheckActiveState::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (AEyeStalk* EyeStalk = EnemyHelpers::GetEyeStalkFromBTComp(OwnerComp))
	{
		return EyeStalk->GetEyeStalkActive();
	}

	return false;
}
