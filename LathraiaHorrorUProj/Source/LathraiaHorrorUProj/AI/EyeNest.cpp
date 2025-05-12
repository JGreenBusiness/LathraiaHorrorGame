// Fill out your copyright notice in the Description page of Project Settings.


#include "EyeNest.h"

#include "EyeStalk.h"

AEyeNest::AEyeNest()
{
    USceneComponent* RootComp = CreateDefaultSubobject<USceneComponent>("Root Component");
    SetRootComponent(RootComp);

    EyeMesh = CreateDefaultSubobject<UStaticMeshComponent>("Root Mesh");
    EyeMesh->SetupAttachment(RootComponent);

    EyeStalkLocation = CreateDefaultSubobject<USceneComponent>("Eye Stalk Location");
    EyeStalkLocation->SetupAttachment(RootComponent);
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
