// Fill out your copyright notice in the Description page of Project Settings.


#include "LHCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInput/Public/InputAction.h"
#include <EnhancedInputComponent.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "Lantern.h"

ALHCharacter::ALHCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	TurnRateGamepad = 45.f;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	

	Mesh1P = Cast<USkeletalMeshComponent>(GetDefaultSubobjectByName(TEXT("CHaracterMesh0")));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	CharacterMovementComponent = GetCharacterMovement();
	DefaultMaxWalkSpeed = CharacterMovementComponent->MaxWalkSpeed;
}

void ALHCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ALHCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (IsValid(Input))
	{
		Input->BindAction(KBLookInputAction, ETriggerEvent::Triggered, this, &ALHCharacter::InputLook);
		Input->BindAction(GamepadLookInputAction, ETriggerEvent::Triggered, this, &ALHCharacter::InputLook);

		Input->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ALHCharacter::InputMove);
		Input->BindAction(SprintInputAction, ETriggerEvent::Started, this, &ALHCharacter::InputSprintBegun);
		Input->BindAction(SprintInputAction, ETriggerEvent::Completed, this, &ALHCharacter::InputSprintEnded);

		Input->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &ALHCharacter::InputJump);

		Input->BindAction(CrouchInputAction, ETriggerEvent::Started, this, &ALHCharacter::InputCrouch);
		Input->BindAction(CrouchInputAction, ETriggerEvent::Completed, this, &ALHCharacter::InputUnCrouch);

		Input->BindAction(InteractInputAction, ETriggerEvent::Triggered, this, &ALHCharacter::InputInteract);

		Input->BindAction(PrimaryInputAction, ETriggerEvent::Triggered, this, &ALHCharacter::InputPrimaryAction);

		Input->BindAction(SecondaryInputAction, ETriggerEvent::Triggered, this, &ALHCharacter::InputSecondaryAction);
		Input->BindAction(SecondaryInputAction, ETriggerEvent::Completed, this, &ALHCharacter::ToggleHeldLantern);

		Input->BindAction(TertiaryInputAction, ETriggerEvent::Triggered, this, &ALHCharacter::InputTertieryAction);
	}
}

void ALHCharacter::OnInteractAction()
{
	OnInteract.Broadcast();
}

void ALHCharacter::ToggleHeldLantern()
{
	if (Lantern)
	{
		Lantern->ToggleLanternHeldState();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("LHCharacter.cpp: Lantern not Set"))
	}
}

void ALHCharacter::PlaceLanternDown()
{
	if (Lantern && Lantern->GetActiveSocketState() != ELanternState::ELS_RekindleReady)
	{
		Lantern->SetLanternState(ELanternState::ELS_RekindleReady);
	}
}

void ALHCharacter::InputMove(const FInputActionValue& InputActionValue)
{
	if (Controller != nullptr)
	{
		const FVector2D MoveValue = InputActionValue.Get<FVector2D>();
		const FRotator MovementRotation(0.0f, Controller->GetControlRotation().Yaw, 0.0f);

		if (MoveValue.X != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::RightVector);
			AddMovementInput(MovementDirection, MoveValue.X);
		}

		if (MoveValue.Y != 0.0f)
		{
			const FVector MovementDirection = MovementRotation.RotateVector(FVector::ForwardVector);
			AddMovementInput(MovementDirection, MoveValue.Y);
		}
	}
}

void ALHCharacter::InputSprintBegun(const FInputActionValue& InputActionValue)
{
	CharacterMovementComponent->MaxWalkSpeed = SprintSpeed;
}

void ALHCharacter::InputSprintEnded(const FInputActionValue& InputActionValue)
{
	CharacterMovementComponent->MaxWalkSpeed = DefaultMaxWalkSpeed;
}

void ALHCharacter::InputLook(const FInputActionValue& InputActionValue)
{
	if (Controller != nullptr)
	{
		const FVector2D LookValue = InputActionValue.Get<FVector2D>();

		if (LookValue.X != 0.0f)
		{
			TurnAtRate(LookValue.X);
		}

		if (LookValue.Y != 0.0f)
		{
			LookUpAtRate(LookValue.Y);
		}
	}
}

void ALHCharacter::InputJump(const FInputActionValue& InputActionValue)
{
	Super::Jump();
}

void ALHCharacter::InputCrouch(const FInputActionValue& InputActionValue)
{
	Super::Crouch();
}

void ALHCharacter::InputUnCrouch(const FInputActionValue& InputActionValue)
{
	Super::UnCrouch();
}

void ALHCharacter::InputInteract(const FInputActionValue& InputActionValue)
{
	OnInteractAction();
}

void ALHCharacter::InputPrimaryAction(const FInputActionValue& InputActionValue)
{
	ToggleHeldLantern();
}

void ALHCharacter::InputSecondaryAction(const FInputActionValue& InputActionValue)
{
	if (Lantern)
	{
		Lantern->SetLanternState(ELanternState::ELS_InUse);
	}
}

void ALHCharacter::InputTertieryAction(const FInputActionValue& InputActionValue)
{
	if (Lantern)
	{
		PlaceLanternDown();
	}
}


void ALHCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ALHCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

