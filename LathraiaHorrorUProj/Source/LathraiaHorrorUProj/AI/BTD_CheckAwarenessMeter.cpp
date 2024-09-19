// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_CheckAwarenessMeter.h"

#include "AIController.h"
#include "EyeStalk.h"

UBTD_CheckAwarenessMeter::UBTD_CheckAwarenessMeter()
{
	NodeName = "Check Awareness Meter";
}

bool UBTD_CheckAwarenessMeter::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (const AAIController* AIController = Cast<AAIController>(OwnerComp.GetOwner()))
	{
		if(AEyeStalk* EyeStalk = Cast<AEyeStalk>(AIController->GetPawn()))
		{
			if (EyeStalk->GetAwarenessMeterValue() > AwarenessMeterMax)
			{
				EyeStalk->SetAwarenessMeterValue(AwarenessMeterMax);
				return true;
			}
		}
	}

	return false;
}
