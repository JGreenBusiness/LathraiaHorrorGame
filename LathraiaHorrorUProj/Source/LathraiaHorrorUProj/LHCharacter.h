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

UCLASS(config = Game)
class LATHRAIAHORRORUPROJ_API ALHCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

public:
	ALHCharacter();

protected:
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

private:
	float DefaultMaxWalkSpeed;

protected:

	void OnInteractAction();

	void ToggleHeldLantern();

	void PlaceLanternDown();

	void TurnAtRate(float Rate);

	void LookUpAtRate(float Rate);

protected:

	UCharacterMovementComponent* CharacterMovementComponent;

	ALantern* Lantern = nullptr;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float TurnRateGamepad;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteract OnInteract;

	UPROPERTY(Category = "LHCharacter Config: Sprinting", EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", UIMin = "0", ForceUnits = "cm/s"))
	float SprintSpeed = 600.0;

	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LHCharacter Config: Enhanced Input")
	UInputAction* SecondaryInputAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LHCharacter Config: Enhanced Input")
	UInputAction* TertiaryInputAction;

public:
	bool HasLantern() { return Lantern != nullptr; }
	void SetLantern(ALantern* NewLantern) { Lantern = NewLantern; }

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

	void InputSecondaryAction(const FInputActionValue& InputActionValue);

	void InputTertieryAction(const FInputActionValue& InputActionValue);
};
