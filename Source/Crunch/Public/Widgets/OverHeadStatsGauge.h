// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OverHeadStatsGauge.generated.h"

class UAbilitySystemComponent;
class UValueGauge;

UCLASS()
class CRUNCH_API UOverHeadStatsGauge : public UUserWidget
{
	GENERATED_BODY()
	
public:

	/**
	 * @brief Binds the overhead gauges to attributes from the provided Ability System Component.
	 * @param AbilitySystemComponent Ability System Component that owns the displayed attributes.
	 */
	void ConfigureWithASC(UAbilitySystemComponent* AbilitySystemComponent);
	
private:

	/** Health gauge widget bound from the widget blueprint. */
	UPROPERTY(meta = (BindWidget))
	UValueGauge* HealthBar;

	/** Mana gauge widget bound from the widget blueprint. */
	UPROPERTY(meta = (BindWidget))
	UValueGauge* ManaBar;
};