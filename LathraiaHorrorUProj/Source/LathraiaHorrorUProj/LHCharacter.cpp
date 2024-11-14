// Fill out your copyright notice in the Description page of Project Settings.


#include "LHCharacter.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInput/Public/InputAction.h"
#include <EnhancedInputComponent.h>
#include "GameFramework/CharacterMovementComponent.h"
#include "Lantern.h"
#include "Kismet/GameplayStatics.h"
#include "InteractionComponent.h"

ALHCharacter::ALHCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	TurnRateGamepad = 45.f;

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	CharacterMovementComponent = GetCharacterMovement();
	DefaultMaxWalkSpeed = CharacterMovementComponent->MaxWalkSpeed;

}

void ALHCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	if (bStartWithLantern && LanternClass)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			// Spawn the Blueprint actor
			FActorSpawnParameters SpawnParams;
			Lantern = World->SpawnActor<ALantern>(LanternClass, GetActorLocation(), GetActorRotation(), SpawnParams);
			SetUpLantern(Lantern);
		}
	}

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

		Input->BindAction(PlaceLanternInputAction, ETriggerEvent::Triggered, this, &ALHCharacter::InputPlaceLanternAction);
		Input->BindAction(PlaceLanternInputAction, ETriggerEvent::Completed, this, &ALHCharacter::DisplaceLantern);
		
		Input->BindAction(RekindleLanternInputAction, ETriggerEvent::Triggered, this, &ALHCharacter::InputRekindleLanternAction);
	}
}

void ALHCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, -1, FColor::Green, FString::Printf(TEXT("Health = %i"), Health));
	}


}

float ALHCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float actualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (Health > 0)
	{
		Health -= actualDamage;
	}
	else
	{
		UGameplayStatics::OpenLevel(GetWorld(), *GetWorld()->GetName(), false);
	}

	return actualDamage;
}

void ALHCharacter::OnInteractAction()
{
	TArray<FHitResult> hitResults;
	if (PerformSphereTrace(hitResults))
	{
		for (auto& hit : hitResults)
		{
			if (AActor* actor = hit.GetActor())
			{
				UInteractionComponent* interactionComponent = actor->FindComponentByClass<UInteractionComponent>();
				if (interactionComponent)
				{
					interactionComponent->Interact();

					if (!Lantern)
					{
						if (ALantern* foundLantern = Cast<ALantern>(actor))
						{
							Lantern = foundLantern;
							SetUpLantern(Lantern);
						}
					}
				}
			}
		}
	}
}

void ALHCharacter::ToggleHeldLantern()
{
	if (Lantern)
	{
		Lantern->ToggleLanternHeldState();
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

void ALHCharacter::InputPlaceLanternAction(const FInputActionValue& InputActionValue)
{
	if (Lantern && Lantern->GetActiveLanternState() != ELanternState::ELS_RekindleReady)
	{
		Lantern->SetLanternState(ELanternState::ELS_RekindleReady);
		bLanternRekindleReady = true;
	}
}

void ALHCharacter::InputRekindleLanternAction(const FInputActionValue& InputActionValue)
{
	if (bLanternRekindleReady && Lantern)
	{
		Lantern->SetLanternState(ELanternState::ELS_Rekindling);
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

void ALHCharacter::SetUpLantern(ALantern* LanternToSetUp)
{
	LanternToSetUp->InitializeLantern(GetMesh());
	LanternToSetUp->AddLanternSocket(ELanternState::ELS_Held, HeldLanternSocketName);
	LanternToSetUp->AddLanternSocket(ELanternState::ELS_InUse, InUseLanternSocketName);
	LanternToSetUp->AddLanternSocket(ELanternState::ELS_Stowed, StowedLanternSocketName);
	LanternToSetUp->AddLanternSocket(ELanternState::ELS_RekindleReady, RekindleLanternSocketName);
	LanternToSetUp->AddLanternSocket(ELanternState::ELS_Rekindling, RekindleLanternSocketName);

	LanternToSetUp->SetLanternState(ELanternState::ELS_Held);
}

bool ALHCharacter::PerformSphereTrace(TArray<FHitResult>& OutHits)
{
	FVector CameraLocation;
	FRotator CameraRotation;
	Controller->GetPlayerViewPoint(CameraLocation, CameraRotation);

	FVector startLocation = CameraLocation;
	FVector endLocation = CameraLocation + (CameraRotation.Vector() * InteractionRadius);


	FCollisionQueryParams CollisionParams;
	bool bHit = GetWorld()->SweepMultiByChannel(
		OutHits,
		startLocation,
		endLocation,
		FQuat::Identity,
		ECC_Visibility,
		FCollisionShape::MakeSphere(50.0f),
		CollisionParams
	);

	return bHit;
}

