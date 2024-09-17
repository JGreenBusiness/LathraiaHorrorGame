// Fill out your copyright notice in the Description page of Project Settings.


#include "LHCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInput/Public/InputAction.h"
#include <EnhancedInputComponent.h>

ALHCharacter::ALHCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	TurnRateGamepad = 45.f;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
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
		Input->BindAction(KBLookInputAction, ETriggerEvent::Triggered, this, &ALHCharacter::Look);
		Input->BindAction(GamepadLookInputAction, ETriggerEvent::Triggered, this, &ALHCharacter::Look);
		Input->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ALHCharacter::Move);
		Input->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &ALHCharacter::Jump);
		Input->BindAction(CrouchInputAction, ETriggerEvent::Triggered, this, &ALHCharacter::Crouch);
		Input->BindAction(CrouchInputAction, ETriggerEvent::Completed, this, &ALHCharacter::UnCrouch);
		Input->BindAction(InteractInputAction, ETriggerEvent::Triggered, this, &ALHCharacter::Interact);
	}
}

void ALHCharacter::OnPrimaryAction()
{
	OnInteract.Broadcast();
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

void ALHCharacter::InputSprint(const FInputActionValue& InputActionValue)
{

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
	OnPrimaryAction();
}


void ALHCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void ALHCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

