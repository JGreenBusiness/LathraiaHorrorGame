// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EyeStalk.generated.h"

class UBehaviorTree;

UCLASS()
class LATHRAIAHORRORUPROJ_API AEyeStalk : public APawn
{
	GENERATED_BODY()

public:
	AEyeStalk();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "Eye Stalk") // Angle in degrees
	float ViewConeAngle = 30;

	UPROPERTY(EditAnywhere, Category = "Eye Stalk") // Range in cm
	float ViewConeRange = 1000;

protected:
	UPROPERTY(EditAnywhere, Category = "Eye Stalk")
	UBehaviorTree* BehaviorTree = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* RootMesh = nullptr;
};
