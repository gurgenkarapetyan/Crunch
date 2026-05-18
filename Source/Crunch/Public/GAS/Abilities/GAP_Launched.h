// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/CGameplayAbility.h"
#include "GAP_Launched.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCH_API UGAP_Launched : public UCGameplayAbility
{
	GENERATED_BODY()
	
public:
	UGAP_Launched();

	/**
	 * @brief Activates the launch ability and launches the owning character.
	 *
	 * @param Handle Ability spec handle.
	 * @param ActorInfo Actor information for the ability owner and avatar.
	 * @param ActivationInfo Activation data for this ability instance.
	 * @param TriggerEventData Gameplay event data containing launch velocity information.
	 */
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, 
		const FGameplayEventData* TriggerEventData
	) override;
	
	/**
	 * @brief Returns the gameplay event tag used to activate the launch ability.
	 * @return Launch ability activation gameplay tag.
	 */
	static FGameplayTag GetLaunchAbilityActivationTag() { return FGameplayTag::RequestGameplayTag("ability.passive.launch.activate"); }
};
