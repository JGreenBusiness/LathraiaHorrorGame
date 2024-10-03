// Fill out your copyright notice in the Description page of Project Settings.


#include "EyeNest.h"

#include "EnemyManager.h"
#include "EyeStalk.h"

AEyeNest::AEyeNest()
{
    RootMesh = CreateDefaultSubobject<UStaticMeshComponent>("Root Mesh");
    SetRootComponent(RootMesh);

    EyeStalkLocation = CreateDefaultSubobject<USceneComponent>("Eye Stalk Location");
    EyeStalkLocation->SetupAttachment(RootComponent);
}

void AEyeNest::BeginPlay()
{
    Super::BeginPlay();

    if (UEnemyManager* EManager = GetWorld()->GetSubsystem<UEnemyManager>())
    {
        EManager->RegisterEyeNest(this);
    }
}

void AEyeNest::AttachEyeStalk(AEyeStalk* EyeStalk)
{
    if (!IsOccupied() && IsValid(EyeStalk))
    {
        EyeStalk->SetActorTransform(EyeStalkLocation->GetComponentTransform());

        if (IsValid(EyeStalk->CurrentEyeNest))
        {
            EyeStalk->CurrentEyeNest->bIsOccupied = false;
        }

        EyeStalk->CurrentEyeNest = this;
        bIsOccupied = true;
    }
    else
    {
        if (GEngine && IsValid(EyeStalk))
        {
            GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, "Tried to move EyeStalk: " + EyeStalk->GetName() + " to occupied EyeNest: " + GetName());
        }
    }
}
