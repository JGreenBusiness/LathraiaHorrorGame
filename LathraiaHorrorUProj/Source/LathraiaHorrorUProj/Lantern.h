// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lantern.generated.h"

class USkeletalMeshSocket;

UENUM()
enum class ELanternSocketType : uint8
{
	ELST_Held,
	ELST_Stowed,
	ELST_Rekindle
};

UCLASS()
class LATHRAIAHORRORUPROJ_API ALantern : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALantern();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Lantern Config")
	bool bSpawnOnPlayer = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lantern Config: Lantern Sockets")
	ELanternSocketType DefaultLanternSocket = ELanternSocketType::ELST_Held;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Lantern Config: Lantern Sockets")
	FName HeldLanternSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lantern Config: Lantern Sockets")
	FName StowedLanternSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lantern Config: Lantern Sockets")
	FName RekindleLanternSocketName;

private:
	TMap<ELanternSocketType, const USkeletalMeshSocket*> LanternSockets;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
