// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EyeNestManager.h"
#include "AI/EnemyManager.h"

AEyeNestManager::AEyeNestManager()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AEyeNestManager::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    if (UEnemyManager* Manager = GetWorld()->GetSubsystem<UEnemyManager>())
    {
        if (Manager->GetEyeNestCount() != EyeNests.Num() && GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Eye Nest Manager is missing some Eye Nest's!");
        }
    }
}
