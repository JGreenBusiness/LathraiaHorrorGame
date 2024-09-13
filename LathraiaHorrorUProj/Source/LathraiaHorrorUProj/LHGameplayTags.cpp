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
	
}

void FLHGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName), FString(TEXT("(Native) ")) + FString(TagComment));
}