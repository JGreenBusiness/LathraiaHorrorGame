// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tendril.generated.h"

class ALHCharacter;
class UBoxComponent;
class AEyeStalk;

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
	// When player collides with us, which EyeStalk's should we aggro?
	UPROPERTY(EditAnywhere, Category = "Tendril Config: General")
	TArray<AEyeStalk*> EyeStalksToAggro = {};

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxCollider = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* TendrilMesh = nullptr;

};
