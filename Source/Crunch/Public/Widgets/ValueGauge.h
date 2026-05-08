// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayEffectTypes.h"
#include "Blueprint/UserWidget.h"
#include "ValueGauge.generated.h"

class UTextBlock;
class UProgressBar;
class UAbilitySystemComponent;

UCLASS()
class CRUNCH_API UValueGauge : public UUserWidget
{
	GENERATED_BODY()

public:

	/**
	 * @brief Initializes the gauge visual state.
	 */
	virtual void NativeConstruct() override;

	/**
	 * @brief Sets the initial value and binds this gauge to gameplay attribute change delegates.
	 * @param AbilitySystemComponent Ability System Component that owns the attributes.
	 * @param Attribute Current value attribute.
	 * @param MaxAttribute Maximum value attribute.
	 */
	void SetAndBoundToGameplayAttribute(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayAttribute& Attribute, const FGameplayAttribute& MaxAttribute);

	/**
	 * @brief Updates the gauge value, progress bar percent, and text.
	 * @param NewValue New current value.
	 * @param NewMaxValue New maximum value.
	 */
	void SetValue(float NewValue, float NewMaxValue);
	
private:

	/**
	 * @brief Handles current attribute value changes.
	 * @param ChangeData Attribute change data containing the new value.
	 */
	void ValueChanged(const FOnAttributeChangeData& ChangeData);

	/**
	 * @brief Handles maximum attribute value changes.
	 * @param ChangeData Attribute change data containing the new max value.
	 */
	void MaxValueChanged(const FOnAttributeChangeData& ChangeData);
	
private:

	/** Cached current value displayed by the gauge. */
	float CachedValue;

	/** Cached maximum value displayed by the gauge. */
	float CachedMaxValue;

	/** Fill color applied to the progress bar. */
	UPROPERTY(EditAnywhere, Category = "Visual")
	FLinearColor BarColor;

	/** Progress bar used to display the current value percentage. */
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UProgressBar* ProgressBar;

	/** Text block used to display the current and maximum values. */
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	UTextBlock* ValueText;
};