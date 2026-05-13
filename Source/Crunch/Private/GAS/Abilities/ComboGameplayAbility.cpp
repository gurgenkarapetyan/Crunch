// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/ComboGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitInputPress.h"
#include "Gas/CAbilitySystemStatics.h"
#include "GameplayTagsManager.h"

UComboGameplayAbility::UComboGameplayAbility()
{
	AbilityTags.AddTag(UCAbilitySystemStatics::GetBasicAttackAbilityTag());
	BlockAbilitiesWithTag.AddTag(UCAbilitySystemStatics::GetBasicAttackAbilityTag());
}

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
		
		UAbilityTask_WaitGameplayEvent* WaitComboChangeEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
			this, 
			GetComboChangedEventTag(), 
			nullptr, 
			false, 
			false
		);
		WaitComboChangeEventTask->EventReceived.AddDynamic(this, &UComboGameplayAbility::ComboChangeEventReceived);
		WaitComboChangeEventTask->ReadyForActivation();
	}
	
	if (K2_HasAuthority())
	{
		UAbilityTask_WaitGameplayEvent* WaitGameplayEventTask = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(this, GetComboTargetEventTag());
		WaitGameplayEventTask->EventReceived.AddDynamic(this, &UComboGameplayAbility::DoDamage);
		WaitGameplayEventTask->ReadyForActivation();
	}
	
	SetupWaitComboInputPress();
}

void UComboGameplayAbility::ComboChangeEventReceived(FGameplayEventData Data)
{
	const FGameplayTag EventTag = Data.EventTag;
	if (EventTag == GetComboChangedEventEndTag())
	{
		NextComboName = NAME_None;
		return;
	}
	
	TArray<FName> TagNames;
	UGameplayTagsManager::Get().SplitGameplayTagFName(EventTag, TagNames);
	NextComboName = TagNames.Last();
}

void UComboGameplayAbility::DoDamage(FGameplayEventData Data)
{
	TArray<FHitResult> HitResults = GetHitResultsFromSweepLocationTargetData(Data.TargetData, TargetSweepSphereRadius);
	
	for (const FHitResult& HitResult : HitResults)
	{
		const TSubclassOf<UGameplayEffect> GameplayEffect = GetGameplayEffectForCurrentCombo();
		const FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(
			GameplayEffect, 
			GetAbilityLevel(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo())
		);
		
		FGameplayEffectContextHandle EffectContext = MakeEffectContext(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo());
		EffectContext.AddHitResult(HitResult);
		
		EffectSpecHandle.Data->SetContext(EffectContext);
		
		ApplyGameplayEffectSpecToTarget(
			GetCurrentAbilitySpecHandle(), 
			CurrentActorInfo, 
			CurrentActivationInfo, 
			EffectSpecHandle, 
			UAbilitySystemBlueprintLibrary::AbilityTargetDataFromActor(HitResult.GetActor())
		);
	}
}

TSubclassOf<UGameplayEffect> UComboGameplayAbility::GetGameplayEffectForCurrentCombo() const
{
	if (const UAnimInstance* OwnerAnimIntance = GetOwnerAnimInstance())
	{
		const FName CurrentSectionName = OwnerAnimIntance->Montage_GetCurrentSection(ComboMontage);
		if (const TSubclassOf<UGameplayEffect>* FoundEffectPtr = DamageEffectMap.Find(CurrentSectionName))
		{
			return *FoundEffectPtr;
		}
	}
	
	return DefaultDamageEffect;
}

void UComboGameplayAbility::SetupWaitComboInputPress()
{
	UAbilityTask_WaitInputPress* WaitInputPress = UAbilityTask_WaitInputPress::WaitInputPress(this);
	WaitInputPress->OnPress.AddDynamic(this, &UComboGameplayAbility::HandleInputPress);
	WaitInputPress->ReadyForActivation();
}

void UComboGameplayAbility::HandleInputPress(float TimeWaited)
{
	SetupWaitComboInputPress();
	TryCommitCombo();
}

void UComboGameplayAbility::TryCommitCombo()
{
	if (NextComboName == NAME_None)
	{
		return;
	}

	UAnimInstance* OwnerAnimIntance = GetOwnerAnimInstance();
	if (!OwnerAnimIntance)
	{
		return;
	}
	
	OwnerAnimIntance->Montage_SetNextSection(OwnerAnimIntance->Montage_GetCurrentSection(ComboMontage), NextComboName, ComboMontage);
}
