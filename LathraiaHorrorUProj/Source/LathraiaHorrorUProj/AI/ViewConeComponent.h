// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ViewConeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LATHRAIAHORRORUPROJ_API UViewConeComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UViewConeComponent();

	UPROPERTY(EditAnywhere, Category = "View Cone", meta=(ClampMin=0, ClampMax=180)) // In degrees
	float Angle = 30.f;
	
	UPROPERTY(EditAnywhere, Category = "View Cone", meta=(ClampMin=1)) // In cm
	float Length = 1000.f;
};
