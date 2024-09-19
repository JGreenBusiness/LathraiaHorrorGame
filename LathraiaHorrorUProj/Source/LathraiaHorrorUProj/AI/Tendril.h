// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tendril.generated.h"

class ALHCharacter;
class UBoxComponent;

UCLASS()
class LATHRAIAHORRORUPROJ_API ATendril : public AActor
{
	GENERATED_BODY()
	
public:
	ATendril();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void DamagePlayer(ALHCharacter* PlayerCharacter);
	void NotifyEyeStalks(ALHCharacter* PlayerCharacter);
	
protected:
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxCollider = nullptr;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* TendrilMesh = nullptr;

};
