// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Array.h"
#include "EyeNest.h"
#include "NewEyeStalk.h"

#include "EyeNestManager.generated.h"

UCLASS()
class LATHRAIAHORRORUPROJ_API AEyeNestManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AEyeNestManager();

	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SpawnEyeStalkAtClosestNest(FVector Point);

	UFUNCTION(BlueprintCallable)
	void SpawnEyeStalksAroundPoint(FVector Point, float Range);

	UFUNCTION(BlueprintCallable)
	void ClearEyeStalks();

private:
	UPROPERTY(EditAnywhere, Category = "Eye Nest Manager")
	TArray<AEyeNest*> EyeNests = {};

	UPROPERTY(EditAnywhere, Category = "Eye Nest Manager")
	TSubclassOf<ANewEyeStalk> EyeStalkToSpawn = nullptr;

};
