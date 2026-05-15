// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CMinionCharacter.h"

#include "AbilitySystemComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GAS/CAbilitySystemStatics.h"

void ACMinionCharacter::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	Super::SetGenericTeamId(NewTeamID);
	
	PickSkinBasesOnTeamID();
}

bool ACMinionCharacter::IsActive() const
{
	return !IsDead();
}

void ACMinionCharacter::Activate() const
{
	RespawnImmediately();
}

void ACMinionCharacter::SetGoal(AActor* Goal) const
{
	if (AAIController* AIController = GetController<AAIController>())
	{
		if (UBlackboardComponent* BlackboardComponent = AIController->GetBlackboardComponent())
		{
			BlackboardComponent->SetValueAsObject(GoalBlackboardKeyName, Goal);
		}
	}
}

void ACMinionCharacter::PickSkinBasesOnTeamID()
{
	if (USkeletalMesh** Skin = SkinMap.Find(GetGenericTeamId()))
	{
		GetMesh()->SetSkeletalMesh(*Skin);
	}
}

void ACMinionCharacter::OnRep_TeamID()
{
	PickSkinBasesOnTeamID();
}
