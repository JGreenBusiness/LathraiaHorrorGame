// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "InputConfig.generated.h"

class UInputAction;
struct FGameplaytag;
/**
 * FTaggedInputAction
 * 
 * Struct used to map an input action to a gameplay input tag.
 */
USTRUCT(BlueprintType)
struct FTaggedInputAction
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, Meta = (Category = "InputTag"))
	FGameplayTag InputTag;
};


/*
* 
* 
*/
UCLASS()
class LATHRAIAHORRORUPROJ_API UInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	//Returns the first input Action associated with a given tag
	const UInputAction* FindInputActionForTag(const FGameplayTag& InputTag) const;

public:
	//List of input actions used by the owner. These input actions are mapped to a gameplay
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitlePropperty = "InputAction"))
	TArray<FTaggedInputAction> TaggedInputActions;
};
