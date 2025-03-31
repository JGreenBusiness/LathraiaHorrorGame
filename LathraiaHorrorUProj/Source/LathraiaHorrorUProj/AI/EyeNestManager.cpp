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
    int32 Index = -1;

    TSet<AEyeNest*> Keys = {};
    EyeNests.GetKeys(Keys);

    TArray<AEyeNest*> KeysArray = Keys.Array();

    for (int IterIndex = 0; IterIndex < KeysArray.Num(); IterIndex++)
    {
        AEyeNest* Nest = KeysArray[IterIndex];
        float CurrentDist = FVector::Dist(Point, Nest->GetActorLocation());

        if (ClosestNest == nullptr || CurrentDist < ClosestDist) 
        {
            ClosestNest = Nest;
            ClosestDist = CurrentDist;
            Index = IterIndex;
        }
    }

    if (!IsValid(ClosestNest))
    {
        GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "Failed to find nest near point: " + Point.ToString());
        return;
    }

    // find the range of the new eye stalk [Index - 1, Index + 2]
    TArray<AEyeNest*> FoundRange;
    if (KeysArray.IsValidIndex(Index - 1)) FoundRange.Add(KeysArray[Index - 1]);
    if (KeysArray.IsValidIndex(Index)) FoundRange.Add(KeysArray[Index]);
    if (KeysArray.IsValidIndex(Index + 1)) FoundRange.Add(KeysArray[Index + 1]);
    if (KeysArray.IsValidIndex(Index + 2)) FoundRange.Add(KeysArray[Index + 2]);

    ANewEyeStalk* EyeStalk = GetWorld()->SpawnActor<ANewEyeStalk>(EyeStalkToSpawn);
    EyeStalk->AttachToEyeNest(ClosestNest, FoundRange);
    EyeStalk->SetEyeStalkType(EEyeStalkType::DOCILE);
    EyeStalk->SetViewConeHalfAngle(EyeNests[ClosestNest].ViewHalfAngle);
    EyeStalk->SetViewConeLength(EyeNests[ClosestNest].ViewDistance);
}

void AEyeNestManager::SpawnEyeStalksAroundPoint(FVector Point, float Range)
{
    for (auto& Pair : EyeNests) 
    {
        float CurrentDist = FVector::Dist(Point, Pair.Key->GetActorLocation());
        if (CurrentDist <= Range) 
        {
            ANewEyeStalk* EyeStalk = GetWorld()->SpawnActor<ANewEyeStalk>(EyeStalkToSpawn);
            EyeStalk->AttachToEyeNest(Pair.Key);
            EyeStalk->SetEyeStalkType(EEyeStalkType::SWIFT);
            EyeStalk->SetViewConeHalfAngle(EyeNests[Pair.Key].ViewHalfAngle);
            EyeStalk->SetViewConeLength(EyeNests[Pair.Key].ViewDistance);
        }
    }
}

void AEyeNestManager::ClearEyeStalks()
{
    TArray<AActor*> EyeStalksInLevel;
    UGameplayStatics::GetAllActorsOfClass(this, ANewEyeStalk::StaticClass(), EyeStalksInLevel);

    for (AActor* EyeStalkActor : EyeStalksInLevel)
    {
        ANewEyeStalk* EyeStalkPtr = Cast<ANewEyeStalk>(EyeStalkActor);
        EyeStalkPtr->Destroy();
    }
}
