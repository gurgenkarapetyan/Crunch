// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GenericTeamAgentInterface.h"
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
	 * @param TargetTeam
	 * @param bDrawDebug If true, draws debug traces for the sweep.
	 * @param bIgnoreSelf If true, ignores the owning avatar actor during the trace.
	 * @return Array of hit results gathered from all sphere sweep traces.
	 */
	TArray<FHitResult> GetHitResultsFromSweepLocationTargetData(
		const FGameplayAbilityTargetDataHandle& TargetDataHandle, 
		float SphereSweepRadius = 30.f,
		ETeamAttitude::Type TargetTeam = ETeamAttitude::Hostile,
		bool bDrawDebug = false, 
		bool bIgnoreSelf = true
	) const;
	
	/**
	 * @brief Launches the owning avatar character using the specified velocity.
	 *
	 * @param PushVelocity Launch velocity applied to the owning character.
	 */
	void PushSelf(const FVector& PushVelocity);
	
	/**
	 * @brief Sends a launch gameplay event to the specified target actor.
	 *
	 * @param Target Actor that receives the launch event.
	 * @param PushVelocity Launch velocity encoded into the gameplay event.
	 */
	void PushTarget(AActor* Target, const FVector& PushVelocity);
	
	/**
	 * @brief Applies a gameplay effect to the actor contained in the provided hit result.
	 *
	 * Adds the hit result to the gameplay effect context before application.
	 *
	 * @param HitResult Hit result containing the target actor.
	 * @param GameplayEffect Gameplay effect class to apply.
	 * @param Level Gameplay effect level.
	 */
	void ApplyGameplayEffectToHitResultActor(const FHitResult& HitResult, const TSubclassOf<UGameplayEffect> GameplayEffect, const int Level = 1);
	
	/**
	 * @brief Returns whether debug traces should be drawn for this ability.
	 * @return True if debug drawing is enabled.
	 */
	UFUNCTION()
	FORCEINLINE bool ShouldDrawDebug() const { return bShouldDrawDebug; }
	
	/**
	 * @brief Returns the owning avatar character.
	 * 
	 * @return Owning avatar character, or nullptr if unavailable.
	 */
	ACharacter* GetOwningAvatarCharacter();
	
private:
	/** Enables debug drawing for gameplay ability traces and targeting helpers. */
	UPROPERTY(EditDefaultsOnly, Category = "DEBUG")
	bool bShouldDrawDebug = false;
	
	/** Cached owning avatar character. */
	UPROPERTY()
	ACharacter* AvatarCharacter;
};