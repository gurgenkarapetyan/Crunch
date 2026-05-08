// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/ComboGameplayAbility.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

void UComboGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (!K2_CommitAbility())
	{
		K2_EndAbility();
		return;
	}
	
	if (HasAuthorityOrPredictionKey(ActorInfo, &ActivationInfo))
	{
		UAbilityTask_PlayMontageAndWait* PlayComboMontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, ComboMontage);
		PlayComboMontageTask->OnBlendOut.AddDynamic(this, &UComboGameplayAbility::K2_EndAbility);
		PlayComboMontageTask->OnCancelled.AddDynamic(this, &UComboGameplayAbility::K2_EndAbility);
		PlayComboMontageTask->OnCompleted.AddDynamic(this, &UComboGameplayAbility::K2_EndAbility);
		PlayComboMontageTask->OnInterrupted.AddDynamic(this, &UComboGameplayAbility::K2_EndAbility);
		PlayComboMontageTask->ReadyForActivation();
	}
}
