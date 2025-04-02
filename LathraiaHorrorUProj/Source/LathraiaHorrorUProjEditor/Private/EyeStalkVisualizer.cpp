// Fill out your copyright notice in the Description page of Project Settings.


#include "EyeStalkVisualizer.h"

#include "NewEyeStalk.h"
#include "EyeNest.h"
#include "EyeNestManager.h"

void FEyeStalkVisualizer::DrawVisualization(const UActorComponent* Component, const FSceneView* View,
                                            FPrimitiveDrawInterface* PDI)
{
	if (!IsValid(Component))
	{
		return;
	}

	const ANewEyeStalk* EyeStalk = Cast<ANewEyeStalk>(Component->GetOwner());
	if (IsValid(EyeStalk))
	{
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

	const AEyeNestManager* EyeNestManager = Cast<AEyeNestManager>(Component->GetOwner());
	if (IsValid(EyeNestManager))
	{
		// For each eye nest, add the view cone
		for (auto& Pair : EyeNestManager->EyeNests)
		{
			// View cone
			DrawWireSphereCappedCone(
				PDI,
				Pair.Key->GetActorTransform(),
				Pair.Value.ViewDistance,
				Pair.Value.ViewHalfAngle,
				12,
				1,
				12,
				FLinearColor(1, 0, 0, 0.5f),
				SDPG_World
			);
		}
	}
}
