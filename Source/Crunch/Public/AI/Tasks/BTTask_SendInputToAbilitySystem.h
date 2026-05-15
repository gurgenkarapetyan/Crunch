// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SendInputToAbilitySystem.generated.h"

enum class ECAbilityInputID : uint8;

/**
 * 
 */
UCLASS()
class CRUNCH_API UBTTask_SendInputToAbilitySystem : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Executes the task and sends the configured input ID to the Ability System Component.
	 *
	 * @param OwnerComp Behavior tree component executing this task.
	 * @param NodeMemory Runtime node memory block.
	 * @return Succeeded if the input was sent successfully, otherwise Failed.
	 */
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
private:
	/** Ability input ID sent to the Ability System Component when this task executes. */
	UPROPERTY(EditAnywhere, Category = "Ability")
	ECAbilityInputID InputID;
};
