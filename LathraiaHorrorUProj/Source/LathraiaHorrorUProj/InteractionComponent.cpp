// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionComponent.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"


UInteractionComponent::UInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	InteractionCollider = GetOwner()->GetComponentByClass<UShapeComponent>();
	if (!IsValid(InteractionCollider))
	{
		UE_LOG(LogTemp, Error, TEXT("UInteractionComponent: No interaction Collider found on object \"%s\". Object must have collision collider"),*GetOwner()->GetFName().ToString());
	}
}


void UInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UInteractionComponent::Interact()
{
	OnInteracted.Broadcast();

}

void UInteractionComponent::RemoveInteractionComponent()
{
	DestroyComponent();
}

