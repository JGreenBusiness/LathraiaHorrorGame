// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_UpdatePlayerLocation.h"

#include "EnemyHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_UpdatePlayerLocation::UBTT_UpdatePlayerLocation()
{
	NodeName = "Update Player Location";

	PlayerLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_UpdatePlayerLocation, PlayerLocationKey));
}

EBTNodeResult::Type UBTT_UpdatePlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ALHCharacter* Player = EnemyHelpers::GetPlayerFromWorld(GetWorld()))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(PlayerLocationKey.SelectedKeyName, Player->GetActorLocation());
	}

	return EBTNodeResult::Succeeded;
}
