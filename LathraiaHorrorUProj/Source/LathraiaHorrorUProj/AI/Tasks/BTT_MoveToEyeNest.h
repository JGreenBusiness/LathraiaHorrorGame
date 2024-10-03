// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_MoveToEyeNest.generated.h"

class AEyeStalk;

UENUM()
enum EEyeStalkMovement
{
	ESMove_Closest UMETA(DisplayName="Closest"),
	ESMove_Default UMETA(DisplayName="Default")
};

/**
 * MoveToEyeNest task node.
 * Moves to an EyeNest based on the movement type.
 */
UCLASS()
class LATHRAIAHORRORUPROJ_API UBTT_MoveToEyeNest : public UBTTaskNode
{
	GENERATED_BODY()

	UBTT_MoveToEyeNest();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	void Move_Closest(AEyeStalk* EyeStalk, UBehaviorTreeComponent& OwnerComp);
	void Move_Default(AEyeStalk* EyeStalk);

protected:
	UPROPERTY(EditAnywhere, Category = "Move To Eye Nest")
	TEnumAsByte<EEyeStalkMovement> MovementType = ESMove_Closest;

	// Point to check for closest EyeNest to.
	UPROPERTY(EditAnywhere, Category = "Move To Eye Nest", meta=(EditCondition="MovementType==EEyeStalkMovement::ESMove_Closest", EditConditionHides))
	FBlackboardKeySelector PointKey;
	
};
