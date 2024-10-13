// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "EnemyManager.generated.h"

class AEyeNest;

/**
 * 
 */
UCLASS()
class LATHRAIAHORRORUPROJ_API UEnemyManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	// Store pointer to 'NewEyeNest'.
	void RegisterEyeNest(AEyeNest* NewEyeNest);

	/*
	* @returns The closest EyeNest to the given point.
	* @param NestsToIgnore Ignores these nests when seaching.
	* @param bIncludeOccupied Should we include occupied nests when searching?
	*/
	AEyeNest* GetClosestEyeNest(FVector Point, TArray<AEyeNest*> NestsToIgnore = {}, bool bIncludeOccupied = false);

protected:
	UPROPERTY()
	TArray<AEyeNest*> EyeNests;
	
};
