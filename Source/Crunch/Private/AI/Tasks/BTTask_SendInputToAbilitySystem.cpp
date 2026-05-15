// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTask_SendInputToAbilitySystem.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

EBTNodeResult::Type UBTTask_SendInputToAbilitySystem::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* OwnerAIComponent = OwnerComp.GetAIOwner();
	if (UAbilitySystemComponent* const OwnerASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OwnerAIComponent->GetPawn()))
	{
		OwnerASC->PressInputID(static_cast<int32>(InputID));
		
		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
