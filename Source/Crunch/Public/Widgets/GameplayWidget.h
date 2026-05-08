// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayWidget.generated.h"

class UAbilitySystemComponent;
class UValueGauge;

UCLASS()
class CRUNCH_API UGameplayWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	/**
	 * @brief Initializes the widget and binds value gauges to the owning player's attributes.
	 */
	virtual void NativeConstruct() override;
	
private:

	/** Health gauge widget bound from the widget blueprint. */
	UPROPERTY(meta = (BindWidget))
	UValueGauge* HealthBar;

	/** Mana gauge widget bound from the widget blueprint. */
	UPROPERTY(meta = (BindWidget))
	UValueGauge* ManaBar;

	/** Cached Ability System Component of the owning player pawn. */
	UPROPERTY()
	UAbilitySystemComponent* OwnerAbilitySystemComponent;
};