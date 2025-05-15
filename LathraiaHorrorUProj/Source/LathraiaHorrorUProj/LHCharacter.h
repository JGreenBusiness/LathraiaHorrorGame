// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LHCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class APostProcessVolume;
class UUserWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteract);


class ALantern;
class USoundCue;
class UPanicManagerComponent;

UCLASS(config = Game)
class LATHRAIAHORRORUPROJ_API ALHCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

public:
	ALHCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void RestartLevel();

private:

protected:
	
	void OnInteractAction();

	void ToggleHeldLantern();

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	void DisplaceLantern() { bLanternRekindleReady = false;}

	void SetUpLantern(ALantern* LanternToSetUp);

	bool PerformSphereTrace(TArray<FHitResult>& OutHits);

	UFUNCTION()
	void OnPanicTierChanged();

	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPanicManagerComponent* PanicManagerComponent;

	UCharacterMovementComponent* CharacterMovementComponent;
	ALantern* Lantern = nullptr;

	UPROPERTY()
	APostProcessVolume* PostProcessVolume = nullptr;

	bool bLanternRekindleReady = false;

public:

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> PauseMenuWidget;

	// Character & Controls
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float TurnRateGamepad;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteract OnInteract;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LHCharacter Config: Interaction")
	float InteractionRadius = 500.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LHCharacter Config: Panic")
	float BreathPanicReduction = 50.0f;

	UPROPERTY(EditAnywhere, Category = "LHCharacter Config: Panic")
	float Vignette_Default = 0.4f;

	UPROPERTY(EditAnywhere, Category = "LHCharacter Config: Panic")
	float Vignette_TierTwo = 0.6f;

	UPROPERTY(EditAnywhere, Category = "LHCharacter Config: Panic")
	float Vignette_TierThree = 0.8f;

	UPROPERTY(EditAnywhere, Category = "LHCharacter Config: Panic")
	float Vignette_TierFour = 1.0f;

	UPROPERTY(Category = "LHCharacter Config", EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s"))
	float SprintSpeed = 600.0f;

	UPROPERTY(Category = "LHCharacter Config", EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s"))
	float DefaultMaxWalkSpeed = 300.0f;

	// Lantern Related Properties

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LHCharacter Config: Lantern")
	bool bStartWithLantern = true;

	UPROPERTY(Category = "LHCharacter Config: Lantern", EditDefaultsOnly)
	TSubclassOf<ALantern> LanternClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LHCharacter Config: Lantern Sockets")
	FName HeldLanternSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LHCharacter Config: Lantern Sockets")
	FName StowedLanternSocketName;

	// Enhanced Input 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LHCharacter Config: Enhanced Input")
	UInputAction* KBLookInputAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LHCharacter Config: Enhanced Input")
	UInputAction* GamepadLookInputAction;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LHCharacter Config: Enhanced Input")
	UInputAction* MoveInputAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LHCharacter Config: Enhanced Input")
	UInputAction*SprintInputAction;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LHCharacter Config: Enhanced Input")
	UInputAction* JumpInputAction;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LHCharacter Config: Enhanced Input")
	UInputAction* CrouchInputAction;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LHCharacter Config: Enhanced Input")
	UInputAction* InteractInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LHCharacter Config: Enhanced Input")
	UInputAction* BreatheInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LHCharacter Config: Enhanced Input")
	UInputAction* PrimaryInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LHCharacter Config: Enhanced Input")
	UInputAction* DebugInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LHCharacter Config: Enhanced Input")
	UInputAction* PauseInputAction;

	///Debugging Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lantern Config")
	bool bDebugModeOn = false;

public:

	UFUNCTION(BlueprintCallable, Category = "LHCharacter Panic")
	UPanicManagerComponent* GetPanicManagerComponent() { return PanicManagerComponent; }

	UFUNCTION(BlueprintCallable, Category = "LHCharacter Config: Lantern")
	float GetLanternFlameIntensity();

	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	// Enhanced Input
	void InputMove(const FInputActionValue& InputActionValue);

	void InputSprintBegun(const FInputActionValue& InputActionValue);

	void InputSprintEnded(const FInputActionValue& InputActionValue);

	void InputLook(const FInputActionValue& InputActionValue);

	void InputJump(const FInputActionValue& InputActionValue);

	void InputCrouch(const FInputActionValue& InputActionValue);

	void InputUnCrouch(const FInputActionValue& InputActionValue);

	void InputInteract(const FInputActionValue& InputActionValue);

	void InputBreathe(const FInputActionValue& InputActionValue);

	void InputPrimaryAction(const FInputActionValue& InputActionValue);

	void InputDebugAction(const FInputActionValue& InputActionValue);

	void InputPauseAction(const FInputActionValue& InputActionValue);

};
