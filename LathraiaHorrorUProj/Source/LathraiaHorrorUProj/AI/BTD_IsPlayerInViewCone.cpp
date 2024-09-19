// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_IsPlayerInViewCone.h"

#include "AIController.h"
#include "EyeStalk.h"
#include "ViewConeComponent.h"
#include "LathraiaHorrorUProj/LHCharacter.h"

UBTD_IsPlayerInViewCone::UBTD_IsPlayerInViewCone()
{
	NodeName = "Is Player In View Cone?";
}

bool UBTD_IsPlayerInViewCone::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	// Trace to player
	// -> Blocked = return false
	// -> Not Blocked = Check Angle

	// Angle to player
	// -> Within threshold = return true
	// -> Not within threshold = return false

	const ALHCharacter* PlayerCharacter = nullptr;
	const AEyeStalk* EyeStalk = nullptr;
	
	if (const APlayerController* PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController()))
	{
		PlayerCharacter = Cast<ALHCharacter>(PlayerController->GetPawn());
	}
	
	if (const AAIController* AIController = Cast<AAIController>(OwnerComp.GetOwner()))
	{
		EyeStalk = Cast<AEyeStalk>(AIController->GetPawn());
	}

	if (PlayerCharacter && EyeStalk)
	{
		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(
			HitResult,
			EyeStalk->GetActorLocation(),
			PlayerCharacter->GetActorLocation(),
			ECC_Visibility);

		if (!HitResult.bBlockingHit && HitResult.Distance <= EyeStalk->GetViewConeComponent()->Length)
		{
			const FVector ToPlayer = (PlayerCharacter->GetActorLocation() - EyeStalk->GetActorLocation()).GetSafeNormal();
			const float Angle = AngleBetweenVectors(EyeStalk->GetActorForwardVector(), ToPlayer);
			
			if (Angle <= (EyeStalk->GetViewConeComponent()->Angle * 0.5f))
			{
				return true;
			}
		}
	}

	return false;
}

float UBTD_IsPlayerInViewCone::AngleBetweenVectors(const FVector& A, const FVector& B) const
{
	const float Dot = FVector::DotProduct(A.GetSafeNormal(), B.GetSafeNormal());
	const float Radians = FMath::Acos(Dot);
	return FMath::RadiansToDegrees(Radians);
}
