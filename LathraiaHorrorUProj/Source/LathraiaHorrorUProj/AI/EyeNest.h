// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EyeNest.generated.h"

class AEyeStalk;

UCLASS()
class LATHRAIAHORRORUPROJ_API AEyeNest : public AActor
{
	GENERATED_BODY()
	
public:	
	AEyeNest();

public:
	void AttachEyeStalk(AEyeStalk* EyeStalk);

	bool IsOccupied() const { return bIsOccupied; }

	const USceneComponent* GetEyeStalkLocation() const { return EyeStalkLocation; }

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* EyeMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* EyeStalkLocation = nullptr;

protected:
	bool bIsOccupied = false;

};
