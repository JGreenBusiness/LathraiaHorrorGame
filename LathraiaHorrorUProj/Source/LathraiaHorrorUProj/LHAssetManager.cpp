// Fill out your copyright notice in the Description page of Project Settings.


#include "LHAssetManager.h"
#include "LHGameplayTags.h"

ULHAssetManager::ULHAssetManager()
{
}

ULHAssetManager& ULHAssetManager::Get()
{
	check(GEngine);
	ULHAssetManager* LHAssetManager = Cast<ULHAssetManager>(GEngine->AssetManager);
	return *LHAssetManager;
}

void ULHAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	//Load Native Tags
	FLHGameplayTags::InitializeNativeTags();
}
