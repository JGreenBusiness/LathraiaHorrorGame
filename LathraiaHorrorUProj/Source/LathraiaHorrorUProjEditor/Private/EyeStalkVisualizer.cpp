// Fill out your copyright notice in the Description page of Project Settings.


#include "EyeStalkVisualizer.h"

#include "EyeStalk.h"
#include "EyeNest.h"

void FEyeStalkVisualizer::DrawVisualization(const UActorComponent* Component, const FSceneView* View,
                                            FPrimitiveDrawInterface* PDI)
{
	const AEyeStalk* EyeStalk = Cast<AEyeStalk>(Component->GetOwner());
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

	// Eye nest
	if (AEyeNest* CurrentNest = EyeStalk->GetDefaultEyeNest())
	{
		FVector ToNest = (CurrentNest->GetActorLocation() - EyeStalk->GetActorLocation());

		FMatrix ArrowMatrix = FScaleRotationTranslationMatrix(
			FVector::OneVector,
			ToNest.Rotation(),
			EyeStalk->GetActorLocation()
		);

		DrawDirectionalArrow(
			PDI,
			ArrowMatrix,
			FLinearColor::Blue,
			ToNest.Length(),
			20.f,
			SDPG_Foreground
		);
	}
}
