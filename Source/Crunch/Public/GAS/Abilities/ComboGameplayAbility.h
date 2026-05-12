// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/CGameplayAbility.h"
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
	static FGameplayTag GetComboChangedEventTag() { return FGameplayTag::RequestGameplayTag("ability.combo.change"); }

	/**
	 * @brief Returns the gameplay event tag used to clear the next combo section.
	 * @return Combo change end gameplay event tag.
	 */
	static FGameplayTag GetComboChangedEventEndTag() { return FGameplayTag::RequestGameplayTag("ability.combo.change.end"); };
	
	/**
	 * @brief Returns the gameplay event tag used to trigger combo damage processing.
	 * @return Combo damage gameplay event tag.
	 */
	static FGameplayTag GetComboTargetEventTag() { return FGameplayTag::RequestGameplayTag("ability.combo.damage"); };
	
private:
	/**
	 * @brief Handles received combo change gameplay events.
	 * 
	 * Updates the next combo section name from the received event tag, or clears it when the combo end tag is received.
	 * 
	 * @param Data Gameplay event data received from the ability task.
	 */
	UFUNCTION()
	void ComboChangeEventReceived(FGameplayEventData Data);
	
	/**
	 * @brief Handles combo damage gameplay events.
	 * 
	 * Called when combo target gameplay event data is received from the ability task.
	 * 
	 * @param Data Gameplay event data containing combo target information.
	 */
	UFUNCTION()
	void DoDamage(FGameplayEventData Data);
	
	/**
	 * @brief Creates and activates a task that waits for combo input presses.
	 */
	void SetupWaitComboInputPress();

	/**
	 * @brief Called when combo input is pressed while the ability is active.
	 * 
	 * Re-registers the input wait task and attempts to commit the next combo section.
	 * 
	 * @param TimeWaited Time elapsed before the input was received.
	 */
	UFUNCTION()
	void HandleInputPress(float TimeWaited);

	/**
	 * @brief Attempts to transition the montage into the next combo section.
	 */
	void TryCommitCombo();
	
	/**
	 * @brief Returns the gameplay effect associated with the currently active combo montage section.
	 *
	 * Uses the current montage section name to look up a gameplay effect inside the damage effect map.
	 * Falls back to the default damage effect if no section-specific effect is found.
	 *
	 * @return Gameplay effect class used for the current combo section.
	 */
	TSubclassOf<UGameplayEffect> GetGameplayEffectForCurrentCombo() const; 
	
private:
	/** Gameplay effects mapped to specific combo montage sections. */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effect")
	TMap<FName, TSubclassOf<UGameplayEffect>> DamageEffectMap;
	
	/** Fallback gameplay effect applied when no section-specific effect exists. */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effect")
	TSubclassOf<UGameplayEffect> DefaultDamageEffect;
	
	/** Radius used for sphere sweep target detection traces. */
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float TargetSweepSphereRadius = 30.f;
	
	/** Animation montage played when this combo ability is activated. */
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* ComboMontage;
	
	/** Name of the next montage section to transition into during the combo. */
	FName NextComboName;
};