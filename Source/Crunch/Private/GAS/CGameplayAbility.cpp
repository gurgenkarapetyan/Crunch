// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/CGameplayAbility.h"

UAnimInstance* UCGameplayAbility::GetOwnerAnimInstance() const
{
	if (const USkeletalMeshComponent* const OwnerSkeletalMeshComponent = GetOwningComponentFromActorInfo())
	{
		return OwnerSkeletalMeshComponent->GetAnimInstance();
	}
	
	return nullptr;
}
