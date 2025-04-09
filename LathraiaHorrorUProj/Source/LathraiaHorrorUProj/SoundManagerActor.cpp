// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundManagerActor.h"
#include "SoundManagerSingleton.h"

void ASoundManagerActor::BeginPlay()
{
	Super::BeginPlay();

	if (auto Singleton = GetWorld()->GetSubsystem<USoundManagerSingleton>())
	{
		Singleton->SetInstance(this);
	}
}
