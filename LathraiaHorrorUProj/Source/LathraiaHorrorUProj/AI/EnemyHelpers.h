// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "AIController.h"
#include "EyeStalk.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "LathraiaHorrorUProj/LHCharacter.h"

namespace EnemyHelpers
{
	static ALHCharacter* GetPlayerFromWorld(const UWorld* World)
	{
		ALHCharacter* Player = nullptr;

		if (World)
		{
			if (const APlayerController* PlayerController = Cast<APlayerController>(World->GetFirstPlayerController()))
			{
				Player = Cast<ALHCharacter>(PlayerController->GetPawn());
			}
		}

		return Player;
	}
	
	static AEyeStalk* GetEyeStalkFromBTComp(const UBehaviorTreeComponent& BTComp)
	{
		AEyeStalk* EyeStalk = nullptr;
	
		if (const AAIController* AIController = Cast<AAIController>(BTComp.GetOwner()))
		{
			EyeStalk = Cast<AEyeStalk>(AIController->GetPawn());
		}

		return EyeStalk;
	}
}
