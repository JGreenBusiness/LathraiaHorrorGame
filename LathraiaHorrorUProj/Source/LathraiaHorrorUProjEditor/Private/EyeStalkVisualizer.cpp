// Fill out your copyright notice in the Description page of Project Settings.


#include "EyeStalkVisualizer.h"

#include "NewEyeStalk.h"
#include "EyeNest.h"

void FEyeStalkVisualizer::DrawVisualization(const UActorComponent* Component, const FSceneView* View,
                                            FPrimitiveDrawInterface* PDI)
{
	if (!IsValid(Component))
	{
		return;
	}

	const ANewEyeStalk* EyeStalk = Cast<ANewEyeStalk>(Component->GetOwner());
	if (!IsValid(EyeStalk))
	{
		return;
	}

	// View cone
	DrawWireSphereCappedCone(
		PDI,
		EyeStalk->GetActorTransform(),
		EyeStalk->GetViewConeLength(),
		EyeStalk->GetViewConeHalfAngle(),
		12,
		1,
		12,
		FLinearColor(1, 0, 0, 0.5f),
		SDPG_World
	);
}
