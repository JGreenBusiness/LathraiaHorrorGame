// Fill out your copyright notice in the Description page of Project Settings.


#include "Tendril.h"

#include "Components/BoxComponent.h"
#include "LathraiaHorrorUProj/LHCharacter.h"

ATendril::ATendril()
{
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	
 	BoxCollider = CreateDefaultSubobject<UBoxComponent>("Box Collider");
	BoxCollider->SetupAttachment(Root);

	TendrilMesh = CreateDefaultSubobject<UStaticMeshComponent>("Tendril Mesh");
	TendrilMesh->SetupAttachment(Root);
}

void ATendril::BeginPlay()
{
	Super::BeginPlay();

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ATendril::OnBeginOverlap);
}

void ATendril::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ALHCharacter* PlayerCharacter = Cast<ALHCharacter>(OtherActor))
	{
		DamagePlayer(PlayerCharacter);
		NotifyEyeStalks(PlayerCharacter);
	}
}

void ATendril::DamagePlayer(ALHCharacter* PlayerCharacter)
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, "Tendril::DamagePlayer");
}

void ATendril::NotifyEyeStalks(ALHCharacter* PlayerCharacter)
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, "Tendril::NotifyEyeStalks");
}
