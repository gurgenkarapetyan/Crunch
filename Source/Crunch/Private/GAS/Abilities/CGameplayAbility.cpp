// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Abilities/CGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "GAS/Abilities/GAP_Launched.h"
#include "Kismet/KismetSystemLibrary.h"

UAnimInstance* UCGameplayAbility::GetOwnerAnimInstance() const
{
	if (const USkeletalMeshComponent* const OwnerSkeletalMeshComponent = GetOwningComponentFromActorInfo())
	{
		return OwnerSkeletalMeshComponent->GetAnimInstance();
	}
	
	return nullptr;
}

TArray<FHitResult> UCGameplayAbility::GetHitResultsFromSweepLocationTargetData(
	const FGameplayAbilityTargetDataHandle& TargetDataHandle, const float SphereSweepRadius, ETeamAttitude::Type TargetTeam, const bool bDrawDebug,
	const bool bIgnoreSelf) const
{
	TArray<FHitResult> OutResults;
	TSet<AActor*> HitActors;
	
	IGenericTeamAgentInterface* OwnerTeamInterface = Cast<IGenericTeamAgentInterface>(GetAvatarActorFromActorInfo());
	
	
	for (const TSharedPtr<FGameplayAbilityTargetData> TargetData : TargetDataHandle.Data)
	{
		const FVector StartLocation = TargetData->GetOrigin().GetTranslation();
		const FVector EndLocation = TargetData->GetEndPoint();
		
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
		ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
		
		TArray<AActor*> ActorsToIgnore;
		if (bIgnoreSelf)
		{
			ActorsToIgnore.Add(GetAvatarActorFromActorInfo());
		}

		const EDrawDebugTrace::Type DrawDebugTrace = bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;
		
		TArray<FHitResult> Results;
		UKismetSystemLibrary::SphereTraceMultiForObjects(
			this, 
			StartLocation, 
			EndLocation, 
			SphereSweepRadius, 
			ObjectTypes, 
			false, 
			ActorsToIgnore, DrawDebugTrace,
			Results, 
			false
		);
		
		for (const FHitResult& Result: Results)
		{
			if (HitActors.Contains(Result.GetActor()))
			{
				continue;
			}
			
			if (OwnerTeamInterface)
			{
				const ETeamAttitude::Type OtherActorTeamAttitude = OwnerTeamInterface->GetTeamAttitudeTowards(*Result.GetActor());
				if (OtherActorTeamAttitude != TargetTeam)
				{
					continue;
				}
			}
			
			HitActors.Add(Result.GetActor());
			OutResults.Add(Result);
		}
	}
	
	return OutResults;
}

void UCGameplayAbility::PushSelf(const FVector& PushVelocity)
{
	if (ACharacter* OwningAvatarCharacter = GetOwningAvatarCharacter())
	{
		OwningAvatarCharacter->LaunchCharacter(PushVelocity, true, true);
	}
}

void UCGameplayAbility::PushTarget(AActor* Target, const FVector& PushVelocity)
{
	if (!Target)
	{
		return;
	}
	
	FGameplayEventData EventData;
	FGameplayAbilityTargetData_SingleTargetHit* HitData = new FGameplayAbilityTargetData_SingleTargetHit();
	FHitResult HitResult;
	HitResult.ImpactNormal = PushVelocity;
	HitData->HitResult = HitResult;
	EventData.TargetData.Add(HitData);
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Target, UGAP_Launched::GetLaunchAbilityActivationTag(), EventData);
}

void UCGameplayAbility::ApplyGameplayEffectToHitResultActor(const FHitResult& HitResult, const TSubclassOf<UGameplayEffect> GameplayEffect, const int Level)
{
	const FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(GameplayEffect, Level);
		
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

ACharacter* UCGameplayAbility::GetOwningAvatarCharacter()
{
	if (!AvatarCharacter)
	{
		AvatarCharacter = Cast<ACharacter>(GetAvatarActorFromActorInfo());
	}
	
	return AvatarCharacter;
}
