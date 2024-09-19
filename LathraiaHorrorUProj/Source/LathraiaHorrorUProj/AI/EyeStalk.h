// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EyeStalk.generated.h"

class UViewConeComponent;
class UBehaviorTree;

UCLASS()
class LATHRAIAHORRORUPROJ_API AEyeStalk : public APawn
{
	GENERATED_BODY()

public:
	AEyeStalk();

protected:
	virtual void BeginPlay() override;

public:
	UViewConeComponent* GetViewConeComponent() const { return ViewCone; }

protected:
	UPROPERTY(EditAnywhere, Category = "Eye Stalk")
	UBehaviorTree* BehaviorTree = nullptr;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* RootMesh = nullptr;

	UPROPERTY(VisibleAnywhere)
	UViewConeComponent* ViewCone = nullptr;
};
