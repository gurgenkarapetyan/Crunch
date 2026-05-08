// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_SendGameplayEvent.generated.h"


UCLASS()
class CRUNCH_API UAN_SendGameplayEvent : public UAnimNotify
{
	GENERATED_BODY()
	
public:

	/**
	 * @brief Called when the notify is triggered by an animation.
	 * @param MeshComp Skeletal mesh component playing the animation.
	 * @param Animation Animation sequence that triggered the notify.
	 * @param EventReference Reference data for this notify event.
	 */
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
private:

	/**
	 * @brief Returns the display name shown for this notify in the animation editor.
	 * @return Last name segment of the gameplay event tag, or None if the tag is invalid.
	 */
	virtual FString GetNotifyName_Implementation() const override;
	
private:

	/** Gameplay event tag sent to the owning actor when this notify is triggered. */
	UPROPERTY(EditAnywhere, Category = "Gameplay Ability")
	FGameplayTag EventTag;
};