// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EyeNest.h"
#include "NewEyeStalk.generated.h"

class AEyeNest;

UCLASS()
class LATHRAIAHORRORUPROJ_API ANewEyeStalk : public AActor
{
	GENERATED_BODY()
	
public:
	ANewEyeStalk();

protected:
	void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	void AttachToEyeNest(AEyeNest* InitialNest, TArray<AEyeNest*> FullRange);

private:
	AEyeNest* GetClosestNestToPlayer();

private:
	UPROPERTY()
	AEyeNest* CurrentNest = nullptr;

	UPROPERTY()
	TArray<AEyeNest*> Range;

	UPROPERTY()
	AActor* PlayerActor = nullptr;

};
