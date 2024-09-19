// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EyeStalk.generated.h"

class UViewConeComponent;
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
	UViewConeComponent* GetViewConeComponent() const { return ViewCone; }
	float GetAwarenessMeterValue() const { return AwarenessMeter; }

	void SetAwarenessMeterValue(const float Value) { AwarenessMeter = Value; }

	void IncreaseAwarenessMeter();

protected:
	UPROPERTY(EditAnywhere, Category = "Eye Stalk")
	UBehaviorTree* BehaviorTree = nullptr;

	UPROPERTY(EditAnywhere, Category = "Eye Stalk")
	bool bIsActive = false;
	
	UPROPERTY(VisibleAnywhere, Category = "Eye Stalk")
	float AwarenessMeter = 0.f;

	UPROPERTY(EditAnywhere, Category = "Eye Stalk|Awareness Modifiers")
	float DistanceMultiplier = 1.f;

	UPROPERTY(EditAnywhere, Category = "Eye Stalk|Awareness Modifiers")
	float AngleMultiplier = 1.f;

	UPROPERTY(EditAnywhere, Category = "Eye Stalk|Awareness Modifiers", meta=(ClampMin=0, ClampMax=1))
	float CrouchMultiplier = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Eye Stalk|Awareness Modifiers", meta=(ClampMin=1))
	float MovingMultiplier = 2.f;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* RootMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	UViewConeComponent* ViewCone = nullptr;
};
