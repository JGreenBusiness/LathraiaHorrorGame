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

private:
	float DefaultMaxWalkSpeed;

protected:
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void OnInteractAction();

	void ToggleHeldLantern();

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

	void DisplaceLantern() { bLanternRekindleReady = false;}

	void SetUpLantern(ALantern* LanternToSetUp);

	bool PerformSphereTrace(TArray<FHitResult>& OutHits);

	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPanicManagerComponent* PanicManagerComponent;

	UCharacterMovementComponent* CharacterMovementComponent;
	ALantern* Lantern = nullptr;

	bool bLanternRekindleReady = false;

	int Health;

public:
	UFUNCTION(BlueprintCallable, Category = "LHCharacter Panic")
	UPanicManagerComponent* GetPanicManagerComponent() { return PanicManagerComponent; }
	
	UFUNCTION()
	void OnPanicTierOne();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LHCharacter Config")
	int MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float TurnRateGamepad;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteract OnInteract;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LHCharacter Config: Interaction")
	float InteractionRadius = 500.0;

	UPROPERTY(Category = "LHCharacter Config", EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s"))
	float SprintSpeed = 600.0;

	UPROPERTY(Category = "LHCharacter Config", EditAnywhere)
	USoundCue* DamageSoundCue = nullptr;

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
	UInputAction* PrimaryInputAction;

public:

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

	void InputPrimaryAction(const FInputActionValue& InputActionValue);

};
