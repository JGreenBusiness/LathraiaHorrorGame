// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lantern.generated.h"

class USkeletalMeshSocket;
class ALHCharacter;

UENUM()
enum class ELanternState : uint8
{
	ELST_Held,
	ELST_Stowed,
	ELST_RekindleReady
};

UCLASS()
class LATHRAIAHORRORUPROJ_API ALantern : public AActor
{
	GENERATED_BODY()
	
public:	
	ALantern();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Lantern Config")
	bool bSpawnOnPlayer = true;

	// Socket Logic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lantern Config: Lantern Sockets")
	ELanternState DefaultLanternSocket = ELanternState::ELST_Held;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Lantern Config: Lantern Sockets")
	FName HeldLanternSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lantern Config: Lantern Sockets")
	FName StowedLanternSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lantern Config: Lantern Sockets")
	FName RekindleLanternSocketName;

protected:
	TMap<ELanternState, const USkeletalMeshSocket*> LanternSockets;

	ALHCharacter* Player;

	ELanternState ActiveLanternState;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetLanternState(ELanternState NewLanternState);

	ELanternState GetActiveSocketState() { return ActiveLanternState; }

	void ToggleLanternHeldState();

};
