// Fill out your copyright notice in the Description page of Project Settings.


#include "ViewConeVisualizer.h"

#include "LathraiaHorrorUProj/AI/EyeStalk.h"
#include "LathraiaHorrorUProj/AI/ViewConeComponent.h"

void FViewConeVisualizer::DrawVisualization(const UActorComponent* Component, const FSceneView* View,
                                            FPrimitiveDrawInterface* PDI)
{
	const UViewConeComponent* ViewCone = Cast<UViewConeComponent>(Component);
	if (!ViewCone)
	{
		return;
	}

	const AEyeStalk* EyeStalk = Cast<AEyeStalk>(ViewCone->GetOwner());
	if (!EyeStalk)
	{
		return;
	}
	
	TArray<FVector> Verts;
	
	DrawWireCone(
		PDI,
		Verts,
		ViewCone->GetComponentTransform(),
		EyeStalk->ViewConeRange,
		EyeStalk->ViewConeAngle,
		12,
		FLinearColor(1, 0, 0, 0.5f),
		SDPG_World,
		5);
}
