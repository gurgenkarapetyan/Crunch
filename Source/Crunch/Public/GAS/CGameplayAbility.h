// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "CGameplayAbility.generated.h"

UCLASS()
class CRUNCH_API UCGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	/**
	 * @brief Returns the animation instance of the owning avatar actor.
	 * @return Anim instance associated with the owner's skeletal mesh component, or nullptr if unavailable.
	 */
	UAnimInstance* GetOwnerAnimInstance() const;
};