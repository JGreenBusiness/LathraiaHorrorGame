// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "EyeStalkManager.generated.h"

class AEyeStalk;

/**
 * 
 */
UCLASS()
class LATHRAIAHORRORUPROJ_API UEyeStalkManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	// Store pointer to 'NewEyeStalk'.
	void RegisterEyeStalk(AEyeStalk* NewEyeStalk);

	/*
	* @param Point The point to find the closest EyeStalk to.
	* @return The activated EyeStalk.
	*/
	AEyeStalk* ActivateClosestEyeStalk(FVector Point);

	/*
	* @param IgnoredEyeStalks EyeStalk's to ignore when finding a random one.
	* @param MaxIterations If we keep finding an ignored / active EyeStalk, we will only run this many times.
	* @return The activated EyeStalk.
	*/
	AEyeStalk* ActivateRandomEyeStalk(TArray<AEyeStalk*> IgnoredEyeStalks, int32 MaxIterations = 10);

protected:
	UPROPERTY()
	TArray<AEyeStalk*> EyeStalks;
	
};
