// Fill out your copyright notice in the Description page of Project Settings.


#include "LHGameplayTags.h"
#include "GameplayTagsManager.h"
#include "Engine/EngineTypes.h"

FLHGameplayTags FLHGameplayTags::GameplayTags;

void FLHGameplayTags::InitializeNativeTags()
{
	UGameplayTagsManager& GameplayTagsManager = UGameplayTagsManager::Get();

	GameplayTags.AddAllTags(GameplayTagsManager);

	GameplayTagsManager.DoneAddingNativeTags();
}

void FLHGameplayTags::AddAllTags(UGameplayTagsManager& Manager)
{
	AddTag(InputTag_Move, "Input.Move", "Move input");
	AddTag(InputTag_Look_Mouse,"Input.Look.Mouse","Look (Mouse) input");
	AddTag(InputTag_Look_Stick,"Input.Look.Stick","Look (Stick) input");
	AddTag(InputTag_Jump,"Input.Jump","Jump input");
	AddTag(InputTag_Interact,"Input.Interact","Interact input");
}

void FLHGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}
