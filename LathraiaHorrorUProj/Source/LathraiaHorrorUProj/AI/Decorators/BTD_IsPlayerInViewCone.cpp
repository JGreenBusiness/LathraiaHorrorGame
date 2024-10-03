// Fill out your copyright notice in the Description page of Project Settings.


#include "BTD_IsPlayerInViewCone.h"

#include "EnemyHelpers.h"
#include "EyeStalk.h"
#include "ViewConeComponent.h"
#include "LHCharacter.h"
#include "MathHelpers.h"
#include "EyeNest.h"

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

	const ALHCharacter* PlayerCharacter = EnemyHelpers::GetPlayerFromWorld(GetWorld());
	const AEyeStalk* EyeStalk = EnemyHelpers::GetEyeStalkFromBTComp(OwnerComp);

	if (PlayerCharacter && EyeStalk)
	{
		FHitResult HitResult;
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(PlayerCharacter);
		Params.AddIgnoredActor(EyeStalk);
		Params.AddIgnoredActor(EyeStalk->GetCurrentEyeNest());
		
		GetWorld()->LineTraceSingleByChannel(
			HitResult,
			EyeStalk->GetActorLocation(),
			PlayerCharacter->GetActorLocation(),
			ECC_Visibility,
			Params);

		const float DistToPlayer = FVector::Distance(EyeStalk->GetActorLocation(), PlayerCharacter->GetActorLocation());
		
		if (!HitResult.bBlockingHit && DistToPlayer <= EyeStalk->GetViewConeComponent()->Length)
		{
			const FVector ToPlayer = (PlayerCharacter->GetActorLocation() - EyeStalk->GetActorLocation()).GetSafeNormal();
			const float Angle = MathHelpers::AngleBetweenVectors(EyeStalk->GetActorForwardVector(), ToPlayer);
			
			if (Angle <= (EyeStalk->GetViewConeComponent()->HalfAngle))
			{
				return true;
			}
		}
	}

	return false;
}
