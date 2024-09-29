// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lantern.generated.h"

class USkeletalMeshSocket;
class UPointLightComponent;

UENUM()
enum class ELanternState : uint8
{
	ELS_Held,
	ELS_Stowed,
	ELS_RekindleReady,
	ELS_Rekindling,
	ELS_InUse
};


UENUM()
enum class EFireIntensityTeir : uint8
{
	EFT_Snuffed,
	EFT_TeirOne,
	EFT_TeirTwo,
	EFT_TeirThree,
	EFT_TeirFour,
	EFT_TeirFive,
};


UCLASS()
class LATHRAIAHORRORUPROJ_API ALantern : public AActor
{
	GENERATED_BODY()
	
public:	
	ALantern();

protected:
	virtual void BeginPlay() override;

	void ChangeLanternState(ELanternState NewLanternState);

	float GetFireIntensityTeirRatio(EFireIntensityTeir FireIntensityTeir) { return static_cast<float>(static_cast<uint8>(FireIntensityTeir)) / static_cast<float>(static_cast<uint8>(EFireIntensityTeir::EFT_TeirFive));}

	float LerpFlameIntensity(float DeltaTime);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lantern Config", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float StowedDimedRatio = .3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lantern Config: Burn Rates", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float HeldBurnRate = .1f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lantern Config: Burn Rates", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float StowedBurnRate = .01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lantern Config: Burn Rates", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float InUseBurnRate = .5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lantern Config: Burn Rates", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float RekindlingBurnRate = .5f;


	// Socket Logic
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lantern Config: Lantern Sockets")
	ELanternState DefaultLanternSocket = ELanternState::ELS_Held;

protected:
	TMap<ELanternState, const USkeletalMeshSocket*> LanternSockets;

	ELanternState CurrentLanternState;
	EFireIntensityTeir FireIntensityTeirDestination = EFireIntensityTeir::EFT_Snuffed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPointLightComponent* PointLightComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LanternMeshComponent;

	float BurnRate = .1f;

	float MaxLanternIntensity = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentFlameIntensity;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetLanternState(USceneComponent* MeshWithLanternSockets,ELanternState NewLanternState);

	ELanternState GetActiveLanternState() { return CurrentLanternState; }

	void ToggleLanternHeldState(USceneComponent* MeshWithLanternSockets);

	void AddLanternSocket(USkeletalMeshComponent* ActorMeshComponent, ELanternState LanternState, FName LanternSocketName);
};
