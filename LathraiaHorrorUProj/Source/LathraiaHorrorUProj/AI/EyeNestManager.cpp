// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EyeNestManager.h"
#include "Kismet/GameplayStatics.h"

AEyeNestManager::AEyeNestManager()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AEyeNestManager::BeginPlay()
{
    Super::BeginPlay();

    GetWorld()->GetTimerManager().SetTimerForNextTick([&]()
        {
            TArray<AActor*> EyeNestsInLevel = {};
            UGameplayStatics::GetAllActorsOfClass(this, AEyeNest::StaticClass(), EyeNestsInLevel);

            if (GEngine && EyeNestsInLevel.Num() != EyeNests.Num())
            {
                // really drill in that we are missing some EyeNest's
                GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Eye Nest Manager is missing some Eye Nest's!");
                GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Eye Nest Manager is missing some Eye Nest's!");
                GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Eye Nest Manager is missing some Eye Nest's!");
            }
        });
}

void AEyeNestManager::SpawnEyeStalkAtClosestNest(FVector Point)
{
    AEyeNest* ClosestNest = nullptr;
    float ClosestDist = FLT_MAX;

    for (AEyeNest* Nest : EyeNests)
    {
        float CurrentDist = FVector::Dist(Point, Nest->GetActorLocation());

        if (ClosestNest == nullptr || CurrentDist < ClosestDist) 
        {
            ClosestNest = Nest;
            ClosestDist = CurrentDist;
        }
    }

    ANewEyeStalk* EyeStalk = GetWorld()->SpawnActor<ANewEyeStalk>(EyeStalkToSpawn);
    EyeStalk->AttachToEyeNest(ClosestNest);
}
