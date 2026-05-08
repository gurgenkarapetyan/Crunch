// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AN_SendTargetGroup.generated.h"


UCLASS()
class CRUNCH_API UAN_SendTargetGroup : public UAnimNotify
{
	GENERATED_BODY()

public:

	/**
	 * @brief Called when the notify is triggered by an animation.
	 *
	 * Creates gameplay target data using consecutive socket pairs and sends the data
	 * to the owning actor through a gameplay event.
	 *
	 * @param MeshComp Skeletal mesh component playing the animation.
	 * @param Animation Animation sequence that triggered the notify.
	 * @param EventReference Reference data for this notify event.
	 */
	virtual void Notify(
		USkeletalMeshComponent* MeshComp,
		UAnimSequenceBase* Animation,
		const FAnimNotifyEventReference& EventReference
	) override;
	
private:

	/** Gameplay event tag sent to the owning actor. */
	UPROPERTY(EditAnywhere, Category = "Gameplay Ability")	
	FGameplayTag EventTag;

	/**
	 * @brief Ordered socket names used to generate sweep start and end locations.
	 *
	 * Each consecutive socket pair generates one target data entry.
	 */
	UPROPERTY(EditAnywhere, Category = "Gameplay Ability")	
	TArray<FName> TargetSocketNames;
};