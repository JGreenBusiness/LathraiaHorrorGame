// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_TickAndCheckTimer.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTT_TickAndCheckTimer::UBTT_TickAndCheckTimer()
{
	NodeName = "Tick And Check Timer";

	TimerKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_TickAndCheckTimer, TimerKey));
	TimerMaxKey.AddFloatFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_TickAndCheckTimer, TimerMaxKey));
}

EBTNodeResult::Type UBTT_TickAndCheckTimer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent())
	{
		if (LastTime == FDateTime::MinValue())
		{
			LastTime = FDateTime::Now();
		}
		
		const float DeltaSeconds = (FDateTime::Now() - LastTime).GetTotalSeconds();
		const float TimerValue = BlackboardComp->GetValueAsFloat(TimerKey.SelectedKeyName) + DeltaSeconds;
		const float TimerMaxValue = BlackboardComp->GetValueAsFloat(TimerMaxKey.SelectedKeyName);

		if (TimerValue >= TimerMaxValue)
		{
			BlackboardComp->SetValueAsFloat(TimerKey.SelectedKeyName, 0.f);
			LastTime = FDateTime::MinValue();
			
			return EBTNodeResult::Succeeded;
		}
		else
		{
			BlackboardComp->SetValueAsFloat(TimerKey.SelectedKeyName, TimerValue);
			LastTime = FDateTime::Now();
			
			return EBTNodeResult::Failed;
		}
	}

	return EBTNodeResult::Failed;
}
