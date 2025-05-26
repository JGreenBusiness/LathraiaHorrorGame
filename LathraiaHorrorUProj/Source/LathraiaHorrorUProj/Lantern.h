// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lantern.generated.h"

class USkeletalMeshSocket;
class UPointLightComponent;
class UInteractionComponent;
class UPanicManagerComponent;

UENUM()
enum class ELanternState : uint8
{
	ELS_InUse,
	ELS_Stowed,
	ELS_Rekindling,
	ELS_ReLighting
};


UCLASS()
class LATHRAIAHORRORUPROJ_API ALantern : public AActor
{
	GENERATED_BODY()
	
public:	
	ALantern();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void ChangeLanternState(ELanternState NewLanternState);

	float LerpFlameIntensity(float DeltaTime);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lantern Config", meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float StowedDimedRatio = .3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lantern Config: Burn Rates", meta = (ClampMin = "0.0",UIMin = "0.0"))
	float HeldBurnRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lantern Config: Burn Rates", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float RekindlingBurnRate = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lantern Config: Burn Rates", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float RekindlingDelay = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lantern Config: Burn Rates", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float RelightLanternDelay = 1.0f;

	///Debugging Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lantern Config")
	bool bDebugModeOn = false;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UInteractionComponent* InteractionComponent;

	UPanicManagerComponent* PanicManagerComponent;

	UFUNCTION()
	void OnInteraction();

	TMap<ELanternState, const USkeletalMeshSocket*> LanternSockets;
	USkeletalMeshComponent* MeshWithLanternSockets;
	ELanternState CurrentLanternState = ELanternState::ELS_Stowed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UPointLightComponent* PointLightComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* LanternMeshComponent;

	float BurnRate = .1f;

	float MaxLanternIntensity = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CurrentFlameIntensity;

public:	
	void InitializeLantern(USkeletalMeshComponent* LanternSocketedMesh, UPanicManagerComponent* PanicManager);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetLanternState(ELanternState NewLanternState);

	float GetFlameIntensityPercent() { return (CurrentFlameIntensity / MaxLanternIntensity); }

	ELanternState GetActiveLanternState() { return CurrentLanternState; }

	UFUNCTION(BlueprintCallable, Category = "Lantern Config: Lantern Sockets")
	const USkeletalMeshSocket* GetActiveLanternSocket();

	UFUNCTION(BlueprintCallable, Category = "Lantern Config: Lantern Sockets")
	USkeletalMeshComponent* GetMeshWithLanternSockets();
	UFUNCTION(BlueprintCallable, Category = "Lantern Config: Lantern Sockets")
	void AttatchLanternToActiveSocket();

	UFUNCTION(BlueprintImplementableEvent, Category = "Lantern Config: Lantern")
	void OnLanternNewLanternState(); // Lantern positional lerping occurs in BP_Lantern Event Graph

	void ToggleLanternHeldState();

	void AddLanternSocket(ELanternState LanternState, FName LanternSocketName); // Lantern Sockets are added in ALHCharacter::SetUpLantern
};
