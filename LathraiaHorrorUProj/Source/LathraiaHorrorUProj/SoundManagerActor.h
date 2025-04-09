// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoundManagerActor.generated.h"

class USoundCue;

UCLASS()
class LATHRAIAHORRORUPROJ_API ASoundManagerActor : public AActor
{
	GENERATED_BODY()
	
public:
	ASoundManagerActor() = default;

	void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TMap<FString, USoundCue*> SoundMap = {};

};
