// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_Print.h"

UBTT_Print::UBTT_Print()
{
	NodeName = "Print";
}

EBTNodeResult::Type UBTT_Print::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(Id, Duration, Color, Message);
	}
	
	return EBTNodeResult::Succeeded;
}
