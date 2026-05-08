// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "CCharacter.generated.h"

class UWidgetComponent;
class UCAttributeSet;
class UCAbilitySystemComponent;

UCLASS()
class CRUNCH_API ACCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACCharacter();
	
	void ServerSideInit();
	void ClientSideInit();	
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PossessedBy(AController* NewController) override;
	
protected:
	virtual void BeginPlay() override;

private:
	bool IsLocallyControlledByPlayer() const;
	
public:
	/*****************************************************************************/
	/**								Gameplay Ability							 */
	/*************************************************************************** */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay Ability")
	UCAbilitySystemComponent* CAbilitySystemComponent;
	
	UPROPERTY()
	UCAttributeSet* CAttributeSet;
	
	/*****************************************************************************/
	/**								     UI								         */
	/*************************************************************************** */
private:
	void ConfigureOverHeadStatusWidget();
	
	void UpdateHeadGaugeVisibility() const;
	
	UPROPERTY(VisibleDefaultsOnly, Category = "UI")
	UWidgetComponent* OverHeadWidgetComponent;
	
	FTimerHandle HeadStatGaugeVisibilityUpdateTimerHandle;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float HeadStatGaugeVisibilityCheckUpdateGap = 1.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float HeadStatGaugeVisibilityRangeSquared = 10000000.f;
};
