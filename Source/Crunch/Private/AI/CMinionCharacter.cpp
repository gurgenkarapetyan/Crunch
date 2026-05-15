// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CMinionCharacter.h"

#include "AbilitySystemComponent.h"
#include "GAS/CAbilitySystemStatics.h"

void ACMinionCharacter::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	Super::SetGenericTeamId(NewTeamID);
	
	PickSkinBasesOnTeamID();
}

bool ACMinionCharacter::IsActive() const
{
	return !GetAbilitySystemComponent()->HasMatchingGameplayTag(UCAbilitySystemStatics::GetDeadStatTag());
}

void ACMinionCharacter::Activate() const
{
	GetAbilitySystemComponent()->RemoveActiveEffectsWithGrantedTags(FGameplayTagContainer(UCAbilitySystemStatics::GetDeadStatTag()));
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
