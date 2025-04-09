// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "SoundManagerSingleton.generated.h"

class ASoundManagerActor;

UCLASS()
class LATHRAIAHORRORUPROJ_API USoundManagerSingleton : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	USoundManagerSingleton() = default;

	void SetInstance(ASoundManagerActor* Inst);

	UFUNCTION(BlueprintCallable)
	void PlaySoundAtLocation(FString SoundName, FVector Location);

private:
	UPROPERTY()
	ASoundManagerActor* ManagerInst = nullptr;

};
