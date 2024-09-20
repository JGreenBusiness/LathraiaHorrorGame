// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lantern.generated.h"

class USkeletalMeshSocket;
class ALHCharacter;
class UPointLightComponent;

UENUM()
enum class ELanternState : uint8
{
	ELS_Held,
	ELS_Stowed,
	ELS_RekindleReady,
	ELS_InUse
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
	ELanternState DefaultLanternSocket = ELanternState::ELS_Held;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Lantern Config: Lantern Sockets")
	FName HeldLanternSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lantern Config: Lantern Sockets")
	FName InUseLanternSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lantern Config: Lantern Sockets")
	FName StowedLanternSocketName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lantern Config: Lantern Sockets")
	FName RekindleLanternSocketName;

protected:
	TMap<ELanternState, const USkeletalMeshSocket*> LanternSockets;

	ALHCharacter* Player;

	ELanternState CurrentLanternState;

	UPROPERTY(VisibleAnywhere)
	UPointLightComponent* PointLightComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LanternMeshComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetLanternState(ELanternState NewLanternState);

	ELanternState GetActiveSocketState() { return CurrentLanternState; }

	void ToggleLanternHeldState();

};
