// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EyeStalk.generated.h"

class AAIController;
class UViewConeComponent;
class UBehaviorTree;

UENUM()
enum EEyeStalkMode
{
	ESM_Surveillance UMETA(DisplayName="Surveillance"),
	ESM_SurveillanceEx UMETA(DisplayName="SurveillanceEx"),
	ESM_Rem UMETA(DisplayName="REM")
};

UENUM()
enum EEyeStalkPhase
{
	ESP_Hunting UMETA(DisplayName="Hunting"),
	ESP_Aggro UMETA(DisplayName="Aggro")
};

UCLASS()
class LATHRAIAHORRORUPROJ_API AEyeStalk : public APawn
{
	GENERATED_BODY()

public:
	AEyeStalk();
	
	virtual void Tick(float DeltaSeconds) override;
	
	UViewConeComponent* GetViewConeComponent() const { return ViewCone; }
	float GetAwarenessMeterValue() const { return AwarenessMeter; }
	EEyeStalkMode GetCurrentEyeStalkMode() const { return CurrentMode; }

	void SetAwarenessMeterValue(const float Value) { AwarenessMeter = Value; }
	void SetEyeStalkMode(const EEyeStalkMode NewMode);
	void SetEyeStalkPhase(const EEyeStalkPhase NewPhase) { CurrentPhase = NewPhase; }
	
	void IncreaseAwarenessMeter();

protected:
	void SelectBehaviorTree();
	UBehaviorTree* GetCurrentTree(const AAIController* AIController);
	
	void Mode_Surveillance(const float DeltaSeconds);
	void Mode_SurveillanceEx(const float DeltaSeconds);
	void Mode_Rem(const float DeltaSeconds);

	void SwingEye(const float SwingSpeed, const float MinimumAngle, const float MaximumAngle);

protected:
	UPROPERTY(EditAnywhere, Category = "Eye Stalk")
	UBehaviorTree* BehaviorTree_Hunting = nullptr;

	UPROPERTY(EditAnywhere, Category = "Eye Stalk")
	UBehaviorTree* BehaviorTree_Aggro = nullptr;

	UPROPERTY(EditAnywhere, Category = "Eye Stalk")
	bool bIsActive = false;
	
	UPROPERTY(VisibleAnywhere, Category = "Eye Stalk|Info")
	float AwarenessMeter = 0.f;

	UPROPERTY(VisibleAnywhere, Category = "Eye Stalk|Info")
	TEnumAsByte<EEyeStalkMode> CurrentMode = ESM_Surveillance;
	
	UPROPERTY(VisibleAnywhere, Category = "Eye Stalk|Info")
	TEnumAsByte<EEyeStalkPhase> CurrentPhase = ESP_Hunting;

	UPROPERTY(EditAnywhere, Category = "Eye Stalk|Awareness Modifiers")
	float DistanceMultiplier = 1.f;

	UPROPERTY(EditAnywhere, Category = "Eye Stalk|Awareness Modifiers")
	float AngleMultiplier = 1.f;

	UPROPERTY(EditAnywhere, Category = "Eye Stalk|Awareness Modifiers", meta=(ClampMin=0, ClampMax=1))
	float CrouchMultiplier = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Eye Stalk|Awareness Modifiers", meta=(ClampMin=1))
	float MovingMultiplier = 2.f;

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* RootMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	UViewConeComponent* ViewCone = nullptr;

	bool SwingDirection = true;
	float YawToPlayer = 0.f;
};