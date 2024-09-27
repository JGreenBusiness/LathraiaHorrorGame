// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EyeStalkManager.h"

#include "EyeStalk.h"

void UEyeStalkManager::RegisterEyeStalk(AEyeStalk* NewEyeStalk)
{
	EyeStalks.AddUnique(NewEyeStalk);
}

void UEyeStalkManager::ActivateClosestEyeStalk(FVector Point)
{
	// Find the closest EyeStalk
	AEyeStalk* Closest = nullptr;
	float ClosestDist = FLT_MAX;

	for (int32 Index = 0; Index < EyeStalks.Num(); Index++)
	{
		AEyeStalk* Current = EyeStalks[Index];

		// If EyeStalk is null or already activated, skip it
		if (!IsValid(Current) || Current->GetEyeStalkActive())
		{
			continue;
		}

		float CurrentDist = FVector::Distance(Point, Current->GetActorLocation());

		if (Closest == nullptr || CurrentDist < ClosestDist)
		{
			Closest = Current;
			ClosestDist = CurrentDist;
		}
	}

	// Activate the closest EyeStalk
	if (IsValid(Closest))
	{
		Closest->SetEyeStalkActive(true);
	}
}

void UEyeStalkManager::ActivateRandomEyeStalk(AEyeStalk* IgnoredEyeStalk, int32 MaxIterations)
{
	int32 RandomIndex = FMath::RandHelper(EyeStalks.Num());
	AEyeStalk* RandomEyeStalk = EyeStalks[RandomIndex];

	// If the random eye stalk is null, ignored, or already active then re-run this function
	if (!IsValid(RandomEyeStalk) || 
		RandomEyeStalk == IgnoredEyeStalk || 
		RandomEyeStalk->GetEyeStalkActive())
	{
		if (MaxIterations > 0)
		{
			ActivateRandomEyeStalk(IgnoredEyeStalk, MaxIterations - 1);
		}
	}
	// Else we activate the random eye stalk
	else
	{
		RandomEyeStalk->SetEyeStalkActive(true);
	}
}