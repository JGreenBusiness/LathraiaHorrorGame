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

	void AttachToEyeNest(AEyeNest* Nest);

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	AEyeNest* DeterminedNest = nullptr;

};
