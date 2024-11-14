// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"

#include "EyeNest.h"

void UEnemyManager::RegisterEyeNest(AEyeNest* NewEyeNest)
{
	EyeNests.AddUnique(NewEyeNest);
}

AEyeNest* UEnemyManager::GetClosestEyeNest(FVector Point, TArray<AEyeNest*> NestsToIgnore, bool bIncludeOccupied)
{
	AEyeNest* Closest = nullptr;
	float ClosestDist = FLT_MAX;

	for (AEyeNest* Nest : EyeNests)
	{
		if (!IsValid(Nest)
			|| NestsToIgnore.Contains(Nest)
			|| Nest->IsOccupied() != bIncludeOccupied)
		{
			continue;
		}

		float NestDist = FVector::Distance(Point, Nest->GetActorLocation());

		if (!IsValid(Closest) || NestDist < ClosestDist)
		{
			Closest = Nest;
			ClosestDist = NestDist;
		}
	}

	return Closest;
}
