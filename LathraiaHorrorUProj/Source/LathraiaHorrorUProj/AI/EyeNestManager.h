// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Array.h"
#include "EyeNest.h"
#include "NewEyeStalk.h"

#include "EyeNestManager.generated.h"

USTRUCT()
struct FViewConeVariables
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	float ViewHalfAngle = 30;

	UPROPERTY(EditAnywhere)
	float ViewDistance = 1000;
};

UCLASS()
class LATHRAIAHORRORUPROJ_API AEyeNestManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AEyeNestManager();

	friend class FEyeStalkVisualizer;

	void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void SpawnEyeStalkAtClosestNest(FVector Point);

	UFUNCTION(BlueprintCallable)
	void SpawnEyeStalksAroundPoint(FVector Point, float Range);

	UFUNCTION(BlueprintCallable)
	void ClearEyeStalks();

private:
	UFUNCTION()
	void OnEnterTier2();

	UFUNCTION()
	void OnEnterTier3();

	UFUNCTION()
	void OnEnterTier4();

private:
	UPROPERTY(EditAnywhere, Category = "Eye Nest Manager")
	TMap<AEyeNest*, FViewConeVariables> EyeNests = {};

	UPROPERTY(EditAnywhere, Category = "Eye Nest Manager")
	TSubclassOf<ANewEyeStalk> EyeStalkToSpawn = nullptr;

	UPROPERTY(EditAnywhere, Category = "Eye Nest Manager")
	float SwiftSpawnRange = 1000.f; // in cm

	UPROPERTY()
	class ALHCharacter* PlayerPtr = nullptr;

};
