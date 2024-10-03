// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EyeStalk.generated.h"

class AAIController;
class UViewConeComponent;
class UBehaviorTree;
class AEyeNest;

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

	friend AEyeNest;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
	
	UViewConeComponent* GetViewConeComponent() const { return ViewCone; }
	float GetAwarenessMeterValue() const { return AwarenessMeter; }
	EEyeStalkMode GetCurrentEyeStalkMode() const { return CurrentMode; }
	AEyeNest* GetCurrentEyeNest() const { return CurrentEyeNest; }
	AEyeNest* GetDefaultEyeNest() const { return DefaultEyeNest; }

	UFUNCTION(BlueprintCallable)
	bool GetEyeStalkActive() const { return bIsActive; }

	void SetAwarenessMeterValue(const float Value) { AwarenessMeter = Value; }
	void SetEyeStalkMode(const EEyeStalkMode NewMode);
	void SetEyeStalkPhase(const EEyeStalkPhase NewPhase) { CurrentPhase = NewPhase; }
	void SetEyeStalkActive(const bool bActive) { bIsActive = bActive; }

	void IncreaseAwarenessMeter();

protected:
	void SelectBehaviorTree();
	UBehaviorTree* GetCurrentTree(const AAIController* AIController);
	
	void Mode_Surveillance(const float DeltaSeconds);
	void Mode_SurveillanceEx(const float DeltaSeconds);
	void Mode_Rem(const float DeltaSeconds);

	void SwingEye(const float SwingSpeed, const float MinimumAngle, const float MaximumAngle);
	void UpdateTreeKeys();
	
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:
	UPROPERTY(EditAnywhere, Category = "Eye Stalk Config: General")
	UBehaviorTree* BehaviorTree_Hunting = nullptr;

	UPROPERTY(EditAnywhere, Category = "Eye Stalk Config: General")
	UBehaviorTree* BehaviorTree_Aggro = nullptr;

	UPROPERTY(EditAnywhere, Category = "Eye Stalk Config: General")
	bool bIsActive = true;
	
	UPROPERTY(VisibleAnywhere, Category = "Eye Stalk Config: Info")
	float AwarenessMeter = 0.f;

	UPROPERTY(VisibleAnywhere, Category = "Eye Stalk Config: Info")
	TEnumAsByte<EEyeStalkMode> CurrentMode = ESM_Surveillance;
	
	UPROPERTY(VisibleAnywhere, Category = "Eye Stalk Config: Info")
	TEnumAsByte<EEyeStalkPhase> CurrentPhase = ESP_Hunting;

	UPROPERTY(EditAnywhere, Category = "Eye Stalk Config: Awareness Modifiers")
	float DistanceMultiplier = 1.f;

	UPROPERTY(EditAnywhere, Category = "Eye Stalk Config: Awareness Modifiers")
	float AngleMultiplier = 1.f;

	UPROPERTY(EditAnywhere, Category = "Eye Stalk Config: Awareness Modifiers", meta=(ClampMin=0, ClampMax=1))
	float CrouchMultiplier = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Eye Stalk Config: Awareness Modifiers", meta=(ClampMin=1))
	float MovingMultiplier = 2.f;

	UPROPERTY(EditAnywhere, Category = "Eye Stalk Config: Mode Modifiers|Surveillance", DisplayName = "Swing Speed", meta=(ClampMin=1))
	float SwingSpeed_Surveillance = 10.f;

	// Minimum swing angle in degrees
	UPROPERTY(EditAnywhere, Category = "Eye Stalk Config: Mode Modifiers|Surveillance", DisplayName = "Swing Angle Min.", meta=(ClampMin=-180, ClampMax=180))
	float SwingAngleMin_Surveillance = -60.f;

	// Maximum swing angle in degrees
	UPROPERTY(EditAnywhere, Category = "Eye Stalk Config: Mode Modifiers|Surveillance", DisplayName = "Swing Angle Max.", meta=(ClampMin=-180, ClampMax=180))
	float SwingAngleMax_Surveillance = 60.f;

	UPROPERTY(EditAnywhere, Category = "Eye Stalk Config: Mode Modifiers|REM", DisplayName = "Swing Speed", meta=(ClampMin=1))
	float SwingSpeed_REM = 50.f;

	// Minimum swing angle in degrees
	UPROPERTY(EditAnywhere, Category = "Eye Stalk Config: Mode Modifiers|REM", DisplayName = "Swing Angle Min.", meta=(ClampMin=-180, ClampMax=180))
	float SwingAngleMin_REM = -30.f;

	// Maximum swing angle in degrees
	UPROPERTY(EditAnywhere, Category = "Eye Stalk Config: Mode Modifiers|REM", DisplayName = "Swing Angle Max.", meta=(ClampMin=-180, ClampMax=180))
	float SwingAngleMax_REM = 30.f;

	UPROPERTY(EditAnywhere, Category = "Eye Stalk Config: Mode Modifiers|REM", DisplayName = "Timer Max.", meta = (ClampMin = 1))
	float REMTimerMax = 5.f;

	UPROPERTY(EditAnywhere, Category = "Eye Stalk Config: Mode Modifiers|SurveillanceEx")
	AEyeNest* DefaultEyeNest = nullptr;

	UPROPERTY(EditAnywhere, Category = "Eye Stalk Config: Mode Modifiers|SurveillanceEx", DisplayName = "Interval Max.", meta = (ClampMin = 1))
	float SurveillanceExTimer_IntervalMax = 5.f;

	UPROPERTY(EditAnywhere, Category = "Eye Stalk Config: Mode Modifiers|SurveillanceEx", DisplayName = "Total Max.", meta = (ClampMin = 1))
	float SurveillanceExTimer_TotalMax = 15.f;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* RootMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	UViewConeComponent* ViewCone = nullptr;

	bool SwingDirection = true;
	float YawToPlayer = 0.f;

	UPROPERTY()
	AEyeNest* CurrentEyeNest = nullptr;
};
