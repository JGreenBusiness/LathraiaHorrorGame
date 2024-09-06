// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "LHAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class LATHRAIAHORRORUPROJ_API ULHAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:

	ULHAssetManager();

	// Returns Asset Manager Singleton
	static ULHAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};
