// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

namespace MathHelpers
{
	// In degrees
	static float AngleBetweenVectors(const FVector& A, const FVector& B)
	{
		const float Dot = FVector::DotProduct(A.GetSafeNormal(), B.GetSafeNormal());
		const float Radians = FMath::Acos(Dot);
		return FMath::RadiansToDegrees(Radians);
	}

	// Clamps a float value in the range 0-1
	static float Clamp01(const float Val)
	{
		return FMath::Clamp(Val, 0, 1);
	}
}
