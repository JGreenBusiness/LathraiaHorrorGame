// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_MoveToEyeNest.h"

#include "EnemyHelpers.h"
#include "EnemyManager.h"
#include "EyeNest.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_MoveToEyeNest::UBTT_MoveToEyeNest()
{
	NodeName = "Move To Eye Nest";

	PointKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_MoveToEyeNest, PointKey));
}

EBTNodeResult::Type UBTT_MoveToEyeNest::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEyeStalk* EyeStalk = EnemyHelpers::GetEyeStalkFromBTComp(OwnerComp);

	if (IsValid(EyeStalk))
	{
		switch (MovementType)
		{
			case ESMove_Closest:	Move_Closest(EyeStalk, OwnerComp);		break;
			case ESMove_Default:	Move_Default(EyeStalk);					break;
		}

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

void UBTT_MoveToEyeNest::Move_Closest(AEyeStalk* EyeStalk, UBehaviorTreeComponent& OwnerComp)
{
	if (UEnemyManager* EManager = EyeStalk->GetWorld()->GetSubsystem<UEnemyManager>())
	{
		FVector Point = OwnerComp.GetBlackboardComponent()->GetValueAsVector(PointKey.SelectedKeyName);

		if (AEyeNest* EyeNest = EManager->GetClosestEyeNest(Point, { EyeStalk->GetDefaultEyeNest(), EyeStalk->GetCurrentEyeNest() }))
		{
			EyeNest->AttachEyeStalk(EyeStalk);
		}
	}
}

void UBTT_MoveToEyeNest::Move_Default(AEyeStalk* EyeStalk)
{
	if (AEyeNest* DefaultNest = EyeStalk->GetDefaultEyeNest())
	{
		DefaultNest->AttachEyeStalk(EyeStalk);
	}
}
