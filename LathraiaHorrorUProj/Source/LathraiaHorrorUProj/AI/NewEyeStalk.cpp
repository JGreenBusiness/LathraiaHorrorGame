// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NewEyeStalk.h"

ANewEyeStalk::ANewEyeStalk()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ANewEyeStalk::AttachToEyeNest(AEyeNest* Nest)
{
	SetActorTransform(Nest->GetEyeStalkLocation()->GetComponentTransform());
	DeterminedNest = Nest;
}

void ANewEyeStalk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

