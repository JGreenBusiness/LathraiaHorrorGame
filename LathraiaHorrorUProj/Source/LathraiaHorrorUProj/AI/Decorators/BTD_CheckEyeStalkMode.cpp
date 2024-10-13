// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_CheckEyeStalkMode.h"

#include "EnemyHelpers.h"

UBTD_CheckEyeStalkMode::UBTD_CheckEyeStalkMode()
{
	NodeName = "Check Eye Stalk Mode";
}

bool UBTD_CheckEyeStalkMode::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (const AEyeStalk* EyeStalk = EnemyHelpers::GetEyeStalkFromBTComp(OwnerComp))
	{
		return (EyeStalk->GetCurrentEyeStalkMode() == CheckMode);
	}
	
	return false;
}
