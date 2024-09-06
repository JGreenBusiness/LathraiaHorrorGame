// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplaytagContainer.h"

class UGameplayTagsManager;

/**
 * LHGameplayTags
 * 
 * Singleton containing native gameplay tags
 */
struct FLHGameplayTags
{
	static const FLHGameplayTags& Get() { return GameplayTags; }

	static void InitializeNativeTags();

	// Input Tags
	FGameplayTag InputTag_Move		;
	FGameplayTag InputTag_Look_Mouse;
	FGameplayTag InputTag_Look_Stick;
	FGameplayTag InputTag_Jump		;
	FGameplayTag InputTag_Interact	;

protected:
	//Registers all tags with GameplayTags Manager
	void AddAllTags(UGameplayTagsManager& Manager);

	//Helper function used by AddAllTagds to register a single tag with GameplayTags Manager
	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);

private:

	static FLHGameplayTags GameplayTags;
};
