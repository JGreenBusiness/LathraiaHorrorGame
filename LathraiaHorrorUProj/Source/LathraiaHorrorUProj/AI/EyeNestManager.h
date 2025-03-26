// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Containers/Array.h"
#include "EyeNest.h"

#include "EyeNestManager.generated.h"

UCLASS()
class LATHRAIAHORRORUPROJ_API AEyeNestManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AEyeNestManager();

	void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Eye Nest Manager")
	TArray<AEyeNest*> EyeNests = {};

};
