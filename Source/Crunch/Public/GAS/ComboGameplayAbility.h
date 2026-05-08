// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/CGameplayAbility.h"
#include "ComboGameplayAbility.generated.h"


UCLASS()
class CRUNCH_API UComboGameplayAbility : public UCGameplayAbility
{
	GENERATED_BODY()
	
public:

	/**
	 * @brief Sets up ability tags and blocking tags for the combo ability.
	 */
	UComboGameplayAbility();

	/**
	 * @brief Activates the combo ability and plays the configured combo montage.
	 *
	 * Ends the ability when the montage blends out, completes, is cancelled, or is interrupted.
	 *
	 * @param Handle Ability spec handle.
	 * @param ActorInfo Actor information for the ability owner and avatar.
	 * @param ActivationInfo Activation data for this ability instance.
	 * @param TriggerEventData Optional event data that triggered the ability.
	 */
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData
	) override;
	
private:

	/** Animation montage played when this combo ability is activated. */
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* ComboMontage;
};