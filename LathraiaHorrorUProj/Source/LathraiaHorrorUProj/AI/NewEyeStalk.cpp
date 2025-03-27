// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NewEyeStalk.h"

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

    AEyeNest* ClosestNest = GetClosestNestToPlayer();
    if (ClosestNest != CurrentNest) 
    {
        SetActorTransform(ClosestNest->GetEyeStalkLocation()->GetComponentTransform());
        CurrentNest = ClosestNest;
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

