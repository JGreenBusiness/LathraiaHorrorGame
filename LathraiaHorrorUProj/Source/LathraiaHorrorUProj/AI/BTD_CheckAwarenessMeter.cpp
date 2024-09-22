// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_CheckAwarenessMeter.h"

#include "EnemyHelpers.h"
#include "EyeStalk.h"

UBTD_CheckAwarenessMeter::UBTD_CheckAwarenessMeter()
{
	NodeName = "Check Awareness Meter";
}

bool UBTD_CheckAwarenessMeter::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (AEyeStalk* EyeStalk = EnemyHelpers::GetEyeStalkFromBTComp(OwnerComp))
	{
		if (EyeStalk->GetAwarenessMeterValue() > AwarenessMeterMax)
		{
			EyeStalk->SetAwarenessMeterValue(AwarenessMeterMax);
			return true;
		}
	}

	return false;
}
