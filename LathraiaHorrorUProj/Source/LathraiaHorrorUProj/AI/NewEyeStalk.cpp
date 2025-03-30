// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NewEyeStalk.h"
#include "MathHelpers.h"

ANewEyeStalk::ANewEyeStalk()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ANewEyeStalk::BeginPlay()
{
	Super::BeginPlay();

	PlayerActor = GetWorld()->GetFirstPlayerController()->GetPawn();
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

    if (IsPlayerInViewCone()) 
    {
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Cyan, "Player in viewcone!");
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

