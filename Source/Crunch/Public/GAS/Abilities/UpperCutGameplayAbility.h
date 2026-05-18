// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/CGameplayAbility.h"
#include "UpperCutGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCH_API UUpperCutGameplayAbility : public UCGameplayAbility
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Activates the uppercut ability and plays the launch montage.
	 *
	 * @param Handle Ability spec handle.
	 * @param ActorInfo Actor information for the ability owner and avatar.
	 * @param ActivationInfo Activation data for this ability instance.
	 * @param TriggerEventData Optional gameplay trigger event data.
	 */
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, 
		const FGameplayEventData* TriggerEventData
	) override;
	
	/**
	 * @brief Returns the gameplay event tag used to trigger uppercut launching.
	 * @return Uppercut launch gameplay event tag.
	 */
	static FGameplayTag GetUpperCutLaunchTag() { return FGameplayTag::RequestGameplayTag("ability.uppercut.launch"); };	

private:
	/**
	 * @brief Launches valid targets detected by the uppercut sweep attack.
	 *
	 * Applies launch velocity and launch damage gameplay effects.
	 *
	 * @param EventData Gameplay event data containing sweep target information.
	 */
	UFUNCTION()
	void StartLaunching(FGameplayEventData EventData);
	
private:
	/** Montage played during the uppercut ability. */
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* UpperCutMontage;
	
	/** Radius used for uppercut target sweep detection. */
	UPROPERTY(EditDefaultsOnly, Category = "Targeting")
	float TargetSweepSphereRadius = 80.f;
	
	/** Upward launch velocity applied during the uppercut attack. */
	UPROPERTY(EditDefaultsOnly, Category = "Launch")
	float UpperCutLaunchSpeed = 1000.f;
	
	/** Gameplay effect applied to launched targets. */
	UPROPERTY(EditDefaultsOnly, Category = "Launch")
	TSubclassOf<UGameplayEffect> LaunchDamageEffect;
};
