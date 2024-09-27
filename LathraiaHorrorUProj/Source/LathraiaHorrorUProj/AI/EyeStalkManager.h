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

	// Activates the closest EyeStalk to the passed in 'Point'.
	void ActivateClosestEyeStalk(FVector Point);

	// Activate random EyeStalk, with optional 'IgnoredEyeStalk' to not activate.
	// @param MaxIterations In the unlikely event we keep finding 'IgnoredEyeStalk' or already active stalks, we will only run 'MaxIterations' times.
	void ActivateRandomEyeStalk(AEyeStalk* IgnoredEyeStalk = nullptr, int32 MaxIterations = 10);

protected:
	UPROPERTY()
	TArray<AEyeStalk*> EyeStalks;
	
};
