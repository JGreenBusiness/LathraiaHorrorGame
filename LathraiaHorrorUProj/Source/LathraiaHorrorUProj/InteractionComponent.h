// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteracted);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LATHRAIAHORRORUPROJ_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInteractionComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Interact();
public:

	void RemoveInteractionComponent();

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteracted OnInteracted;

	UShapeComponent* InteractionCollider;
};
