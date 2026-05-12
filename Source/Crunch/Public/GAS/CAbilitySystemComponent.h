// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CAbilitySystemComponent.generated.h"

enum class ECAbilityInputID : uint8;

UCLASS()
class CRUNCH_API UCAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	UCAbilitySystemComponent();
	
	/**
	 * @brief Applies all configured initial gameplay effects to this Ability System Component.
	 *
	 * Only runs on the authority.
	 */
	void ApplyInitialEffects();

	/**
	 * @brief Grants all configured startup abilities to this Ability System Component.
	 *
	 * Only runs on the authority.
	 */
	void GiveInitialAbilities();
	
	/**
	 * @brief Applies the configured full stat restoration gameplay effect.
	 *
	 * Only executes on the authority.
	 */
	void ApplyFullStatEffect();
	
private:
	/**
	 * @brief Applies a gameplay effect to the owning actor on the authority.
	 *
	 * @param GameplayEffect Gameplay effect class to apply.
	 * @param Level Gameplay effect level.
	 */
	void AuthApplyGameplayEffect(TSubclassOf<UGameplayEffect> GameplayEffect, int Level = 1);
	
	/**
	 * @brief Called when the Health attribute value changes.
	 *
	 * Applies the death effect when health reaches zero.
	 *
	 * @param ChangeData Health attribute change data.
	 */
	void HealthUpdated(const FOnAttributeChangeData& ChangeData);
	
private:
	/** Gameplay effects applied when the character is initialized. */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TArray<TSubclassOf<UGameplayEffect>> InitalEffects;

	/** Gameplay effect applied when the owner dies. */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TSubclassOf<UGameplayEffect> DeathEffect;
	
	/** Gameplay effect used to fully restore the owner's stats. */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TSubclassOf<UGameplayEffect> FullStatEffect;
	
	/** Input-bound gameplay abilities granted during initialization. */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities")
	TMap<ECAbilityInputID, TSubclassOf<UGameplayAbility>> Abilities;

	/** Basic input-bound gameplay abilities granted during initialization. */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities")
	TMap<ECAbilityInputID, TSubclassOf<UGameplayAbility>> BasicAbilities;
};