// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CAbilitySystemStatics.generated.h"


UCLASS()
class CRUNCH_API UCAbilitySystemStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	/**
	 * @brief Returns the gameplay tag used by basic attack abilities.
	 * @return Basic attack ability gameplay tag.
	 */
	static FGameplayTag GetBasicAttackAbilityTag();

	/**
	 * @brief Return the gameplay tag used to detect character death
	 * @return dead ability gameplay tag.
	 */
	static FGameplayTag GetDeadStatTag();
};