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
	
	/**
	 * @brief Performs sphere sweep traces using start and end locations stored inside gameplay ability target data.
	 *
	 * Iterates through all target data entries, performs multi sphere traces against pawn object types,
	 * and collects all hit results.
	 *
	 * @param TargetDataHandle Target data handle containing sweep start and end locations.
	 * @param SphereSweepRadius Radius used for the sphere sweep trace.
	 * @param bDrawDebug If true, draws debug traces for the sweep.
	 * @param bIgnoreSelf If true, ignores the owning avatar actor during the trace.
	 * @return Array of hit results gathered from all sphere sweep traces.
	 */
	TArray<FHitResult> GetHitResultsFromSweepLocationTargetData(
		const FGameplayAbilityTargetDataHandle& TargetDataHandle, 
		float SphereSweepRadius = 30.f, 
		bool bDrawDebug = false, 
		bool bIgnoreSelf = true
	) const;
};