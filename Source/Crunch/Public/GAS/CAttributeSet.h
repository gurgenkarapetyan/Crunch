// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "CAttributeSet.generated.h"

/** Generates standard Gameplay Attribute accessors for the given attribute. */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class CRUNCH_API UCAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:

	/** Health attribute accessors. */
	ATTRIBUTE_ACCESSORS(UCAttributeSet, Health)

	/** Max health attribute accessors. */
	ATTRIBUTE_ACCESSORS(UCAttributeSet, MaxHealth)

	/** Mana attribute accessors. */
	ATTRIBUTE_ACCESSORS(UCAttributeSet, Mana)

	/** Max mana attribute accessors. */
	ATTRIBUTE_ACCESSORS(UCAttributeSet, MaxMana)

	/**
	 * @brief Registers replicated attributes.
	 * @param OutLifetimeProps Lifetime replication properties.
	 */
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
private:

	/**
	 * @brief Called when Health is replicated.
	 * @param OldValue Previous replicated health value.
	 */
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);

	/**
	 * @brief Called when MaxHealth is replicated.
	 * @param OldValue Previous replicated max health value.
	 */
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	/**
	 * @brief Called when Mana is replicated.
	 * @param OldValue Previous replicated mana value.
	 */
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue);

	/**
	 * @brief Called when MaxMana is replicated.
	 * @param OldValue Previous replicated max mana value.
	 */
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue);
	
private:

	/** Current health value. */
	UPROPERTY(ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;

	/** Maximum health value. */
	UPROPERTY(ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;

	/** Current mana value. */
	UPROPERTY(ReplicatedUsing = OnRep_Mana)
	FGameplayAttributeData Mana;

	/** Maximum mana value. */
	UPROPERTY(ReplicatedUsing = OnRep_MaxMana)
	FGameplayAttributeData MaxMana;
};