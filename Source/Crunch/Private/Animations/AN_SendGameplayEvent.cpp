// Fill out your copyright notice in the Description page of Project Settings.


#include "Animations/AN_SendGameplayEvent.h"
#include "GameplayTagsManager.h"
#include "AbilitySystemBlueprintLibrary.h"

void UAN_SendGameplayEvent::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                   const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	
	if (MeshComp->GetOwner() == nullptr)
	{
		return;
	}

	if (const UAbilitySystemComponent* OwnerASC  = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(MeshComp->GetOwner()); OwnerASC == nullptr)
	{
		return;
	}
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComp->GetOwner(), EventTag, FGameplayEventData());
}

FString UAN_SendGameplayEvent::GetNotifyName_Implementation() const
{
	if (EventTag.IsValid())
	{
		TArray<FName> TagNames;
		UGameplayTagsManager::Get().SplitGameplayTagFName(EventTag, TagNames);
		
		return TagNames.Last().ToString();
	}
	
	return "None";
}
