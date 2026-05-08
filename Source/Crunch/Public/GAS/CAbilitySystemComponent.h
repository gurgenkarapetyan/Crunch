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
	
private:

	/** Gameplay effects applied when the character is initialized. */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects")
	TArray<TSubclassOf<UGameplayEffect>> InitalEffects;

	/** Input-bound gameplay abilities granted during initialization. */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities")
	TMap<ECAbilityInputID, TSubclassOf<UGameplayAbility>> Abilities;

	/** Basic input-bound gameplay abilities granted during initialization. */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities")
	TMap<ECAbilityInputID, TSubclassOf<UGameplayAbility>> BasicAbilities;
};