// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplaytagContainer.h"

class UGameplayTagsManager;

struct FLHGameplayTags
{
	static const FLHGameplayTags& Get() { return GameplayTags; }

	static void InitializeNativeTags();


protected:
	void AddAllTags(UGameplayTagsManager& Manager);

	void AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment);

private:

	static FLHGameplayTags GameplayTags;
};
