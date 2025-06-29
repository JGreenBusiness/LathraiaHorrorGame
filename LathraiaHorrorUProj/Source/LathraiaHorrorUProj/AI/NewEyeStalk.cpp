// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NewEyeStalk.h"
#include "MathHelpers.h"
#include "LHCharacter.h"
#include "PanicManagerComponent.h"
#include <Kismet/KismetMathLibrary.h>
#include "SoundManagerSingleton.h"

ANewEyeStalk::ANewEyeStalk()
{
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* EyeRoot = CreateDefaultSubobject<USceneComponent>("Eye Root");
	SetRootComponent(EyeRoot);

	EyeMesh = CreateDefaultSubobject<UStaticMeshComponent>("Eye Mesh");
	EyeMesh->SetupAttachment(EyeRoot);
}

void ANewEyeStalk::BeginPlay()
{
	Super::BeginPlay();

	PlayerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
	PanicManagerComp = Cast<ALHCharacter>(PlayerActor)->GetPanicManagerComponent();

	// Play spawn sound
	if (USoundManagerSingleton* SoundManager = GetWorld()->GetSubsystem<USoundManagerSingleton>())
	{
		SoundManager->PlaySoundAtLocation(Sound_Spawn, GetActorLocation());
	}
}

void ANewEyeStalk::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// technically the player is no longer seen by this destroyed eye stalk, so revert to previous panic rate
	if (bPreviousPlayerSeen)
	{
		PanicManagerComp->bIsInLineOfSight = false;
	}

	// Play de-spawn sound
	if (USoundManagerSingleton* SoundManager = GetWorld()->GetSubsystem<USoundManagerSingleton>())
	{
		SoundManager->PlaySoundAtLocation(Sound_Despawn, GetActorLocation());
	}
}

void ANewEyeStalk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Type == EEyeStalkType::DOCILE)
	{
		AEyeNest* ClosestNest = GetClosestNestToPlayer();
		if (ClosestNest != CurrentNest)
		{
			SetActorTransform(ClosestNest->GetEyeStalkLocation()->GetComponentTransform());
			CurrentNest = ClosestNest;
		}
	}

	bool bPlayerSeen = IsPlayerInViewCone();
	if (bPreviousPlayerSeen != bPlayerSeen)
	{
		PanicManagerComp->bIsInLineOfSight = bPlayerSeen;
		bPreviousPlayerSeen = bPlayerSeen;

		// Play correct sound when player seen state changes
		if (USoundManagerSingleton* SoundManager = GetWorld()->GetSubsystem<USoundManagerSingleton>())
		{
			SoundManager->PlaySoundAtLocation(bPlayerSeen ? Sound_PlayerSeen : Sound_PlayerLost, GetActorLocation());
		}

		if (ALHCharacter* Character = Cast<ALHCharacter>(PlayerActor))
		{
			Character->SetVignetteOverride(bPlayerSeen);
		}
	}

	// Rotate to look at player
	if (bPlayerSeen)
	{
		FVector PlayerLocation = PlayerActor->GetActorLocation();
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(EyeMesh->GetComponentLocation(), PlayerLocation);

		EyeMesh->SetWorldRotation(LookAtRotation);
	}
	// Lerp back to original rotation
	else
	{
		// Random rotation value
		if (bLerping)
		{
			FRotator RandomRotation = FRotator(0, RandomAngle, 0);
			FRotator NewEyeRotation = UKismetMathLibrary::RInterpTo(EyeMesh->GetRelativeRotation(), RandomRotation, DeltaTime, LerpSpeed);
			EyeMesh->SetRelativeRotation(NewEyeRotation);

			if (NewEyeRotation.Equals(RandomRotation, 2.f))
			{
				bLerping = false;
			}
		}
		else
		{
			RandomAngle = FMath::RandRange(-RandomHalfAngleRange, RandomHalfAngleRange);
			bLerping = true;

			// Play idle sound
			if (USoundManagerSingleton* SoundManager = GetWorld()->GetSubsystem<USoundManagerSingleton>())
			{
				SoundManager->PlaySoundAtLocation(Sound_Idle, GetActorLocation());
			}
		}
	}
}

void ANewEyeStalk::AttachToEyeNest(AEyeNest* InitialNest, TArray<AEyeNest*> FullRange)
{
    SetActorTransform(InitialNest->GetEyeStalkLocation()->GetComponentTransform());
    CurrentNest = InitialNest;
    Range = FullRange;
}

AEyeNest* ANewEyeStalk::GetClosestNestToPlayer()
{
    // loop over every nest in range, move to that nest if it is the new closest one
    AEyeNest* ClosestNest = CurrentNest;
    float ClosestDist = FVector::Dist(PlayerActor->GetActorLocation(), CurrentNest->GetActorLocation());

    for (AEyeNest* Nest : Range)
    {
        float CurrentDist = FVector::Dist(PlayerActor->GetActorLocation(), Nest->GetActorLocation());

        if (ClosestNest == nullptr || CurrentDist < ClosestDist)
        {
            ClosestNest = Nest;
            ClosestDist = CurrentDist;
        }
    }

    return ClosestNest;
}

bool ANewEyeStalk::IsPlayerInViewCone()
{
	// Trace to player
	// -> Blocked = return false
	// -> Not Blocked = Check Angle

	// Angle to player
	// -> Within threshold = return true
	// -> Not within threshold = return false

	if (PlayerActor)
	{
		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(PlayerActor);
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(CurrentNest);

		GetWorld()->LineTraceSingleByChannel(
			HitResult,
			GetActorLocation(),
			PlayerActor->GetActorLocation(),
			ECC_Visibility,
			Params);

		const float DistToPlayer = FVector::Distance(GetActorLocation(), PlayerActor->GetActorLocation());

		if (!HitResult.bBlockingHit && DistToPlayer <= ViewCone_Length)
		{
			const FVector ToPlayer = (PlayerActor->GetActorLocation() - GetActorLocation()).GetSafeNormal();
			const float Angle = MathHelpers::AngleBetweenVectors(GetActorForwardVector(), ToPlayer);

			if (Angle <= ViewCone_HalfAngle)
			{
				return true;
			}
		}
	}

	return false;
}

