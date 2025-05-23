// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundManagerSingleton.h"
#include "SoundManagerActor.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void USoundManagerSingleton::SetInstance(ASoundManagerActor* Inst)
{
    if (IsValid(Inst))
    {
        ManagerInst = Inst;
    }
}

void USoundManagerSingleton::PlaySoundAtLocation(FString SoundName, FVector Location)
{
    if (!IsValid(ManagerInst))
    {
        GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, "No valid Sound Manager instance!");
        return;
    }

    if (SoundName == "")
    {
        GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, "Sound name is empty!");
        return;
    }

    USoundCue* SoundPtr = ManagerInst->SoundMap[SoundName];
    if (SoundPtr == nullptr)
    {
        GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, "No valid sound with the name: " + SoundName);
        return;
    }

    UGameplayStatics::PlaySoundAtLocation(ManagerInst, SoundPtr, Location);
}
