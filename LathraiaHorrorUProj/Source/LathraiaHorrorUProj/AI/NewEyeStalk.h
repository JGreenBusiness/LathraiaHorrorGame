// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EyeNest.h"
#include "NewEyeStalk.generated.h"

class AEyeNest;

UENUM()
enum EEyeStalkType 
{
	DOCILE = 0,
	SWIFT
};

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
	void AttachToEyeNest(AEyeNest* InitialNest, TArray<AEyeNest*> FullRange = {});

	float GetViewConeLength() const { return ViewCone_Length; }
	float GetViewConeHalfAngle() const { return ViewCone_HalfAngle; }

	void SetEyeStalkType(EEyeStalkType NewType) { Type = NewType; }
	void SetViewConeHalfAngle(float HalfAngle) { ViewCone_HalfAngle = HalfAngle; }
	void SetViewConeLength(float Length) { ViewCone_Length = Length; }

private:
	AEyeNest* GetClosestNestToPlayer();
	bool IsPlayerInViewCone();

private:
	UPROPERTY()
	AEyeNest* CurrentNest = nullptr;

	UPROPERTY()
	TArray<AEyeNest*> Range;

	UPROPERTY()
	AActor* PlayerActor = nullptr;

	UPROPERTY(EditAnywhere, Category = "New Eye Stalk", meta = (ClampMin = 0, ClampMax = 90)) // In degrees
		float ViewCone_HalfAngle = 30.f;

	UPROPERTY(EditAnywhere, Category = "New Eye Stalk", meta = (ClampMin = 1)) // In cm
		float ViewCone_Length = 1000.f;

	UPROPERTY(VisibleAnywhere, Category = "New Eye Stalk")
	TEnumAsByte<EEyeStalkType> Type;

};
