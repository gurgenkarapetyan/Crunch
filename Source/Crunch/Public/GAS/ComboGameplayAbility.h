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
	
	/**
	 * @brief Returns the gameplay event tag used to listen for combo section changes.
	 * @return Combo change gameplay event tag.
	 */
	static FGameplayTag GetComboChangedEventTag();

	/**
	 * @brief Returns the gameplay event tag used to clear the next combo section.
	 * @return Combo change end gameplay event tag.
	 */
	static FGameplayTag GetComboChangedEventEndTag();
	
private:
	/**
	 * @brief Handles received combo change gameplay events.
	 * Updates the next combo section name from the received event tag, or clears it when the combo end tag is received.
	 * @param Data Gameplay event data received from the ability task.
	 */
	UFUNCTION()
	void ComboChangeEventReceived(FGameplayEventData Data);
	
	/**
	 * @brief Creates and activates a task that waits for combo input presses.
	 */
	void SetupWaitComboInputPress();

	/**
	 * @brief Called when combo input is pressed while the ability is active.
	 * Re-registers the input wait task and attempts to commit the next combo section.
	 * @param TimeWaited Time elapsed before the input was received.
	 */
	UFUNCTION()
	void HandleInputPress(float TimeWaited);

	/**
	 * @brief Attempts to transition the montage into the next combo section.
	 */
	void TryCommitCombo();
	
private:
	/** Animation montage played when this combo ability is activated. */
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* ComboMontage;
	
	/** Name of the next montage section to transition into during the combo. */
	FName NextComboName;
};