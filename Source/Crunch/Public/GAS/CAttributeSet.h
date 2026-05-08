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

	/**
	 *	An "On Aggregator Change" type of event could go here, and that could be called when active gameplay effects are added or removed to an attribute aggregator.
	 *	It is difficult to give all the information in these cases though - aggregators can change for many reasons: being added, being removed, being modified, having a modifier change, immunity, stacking rules, etc.
	 */

	/**
	 *	Called just before any modification happens to an attribute. This is lower level than PreAttributeModify/PostAttribute modify.
	 *	There is no additional context provided here since anything can trigger this. Executed effects, duration based effects, effects being removed, immunity being applied, stacking rules changing, etc.
	 *	This function is meant to enforce things like "Health = Clamp(Health, 0, MaxHealth)" and NOT things like "trigger this extra thing if damage is applied, etc".
	 *	
	 *	NewValue is a mutable reference so you are able to clamp the newly applied value as well.
	 */
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	/**
	 *	Called just after a GameplayEffect is executed to modify the base value of an attribute. No more changes can be made.
	 *	Note this is only called during an 'execute'. E.g., a modification to the 'base value' of an attribute. It is not called during an application of a GameplayEffect, such as a 5 ssecond +10 movement speed buff.
	 */
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;
	
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