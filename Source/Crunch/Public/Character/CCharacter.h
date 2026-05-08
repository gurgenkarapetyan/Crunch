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

	/**
	 * @brief Sets up character components, collision, ability system, attributes, and overhead UI.
	 */
	ACCharacter();

	/**
	 * @brief Initializes ability actor info, applies initial effects, and grants initial abilities on the server.
	 */
	void ServerSideInit();

	/**
	 * @brief Initializes ability actor info on the owning client.
	 */
	void ClientSideInit();

	/**
	 * @brief Called every frame.
	 * @param DeltaTime Time elapsed since the previous frame.
	 */
	virtual void Tick(float DeltaTime) override;

	/**
	 * @brief Binds input actions for this character.
	 * @param PlayerInputComponent Input component used to bind player controls.
	 */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**
	 * @brief Called when the character is possessed by a controller.
	 * @param NewController Controller that now possesses this character.
	 */
	virtual void PossessedBy(AController* NewController) override;
	
protected:

	/**
	 * @brief Called when the game starts or when the character is spawned.
	 */
	virtual void BeginPlay() override;

private:

	/**
	 * @brief Checks whether this character is controlled by a local player controller.
	 * @return True if the character is locally controlled by a player.
	 */
	bool IsLocallyControlledByPlayer() const;
	
public:

	/*****************************************************************************/
	/**								Gameplay Ability							 */
	/*************************************************************************** */

	/**
	 * @brief Returns this character's Ability System Component.
	 * @return Ability System Component owned by this character.
	 */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
private:

	/** Ability System Component used to manage abilities, effects, tags, and gameplay cues. */
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay Ability")
	UCAbilitySystemComponent* CAbilitySystemComponent;

	/** Attribute Set containing this character's gameplay attributes. */
	UPROPERTY()
	UCAttributeSet* CAttributeSet;
	
	/*****************************************************************************/
	/**								     UI								         */
	/*************************************************************************** */
private:

	/**
	 * @brief Configures the overhead status widget and binds it to the Ability System Component.
	 */
	void ConfigureOverHeadStatusWidget();

	/**
	 * @brief Updates overhead status gauge visibility based on distance from the local player.
	 */
	void UpdateHeadGaugeVisibility() const;

	/** Widget component used to display overhead stats above the character. */
	UPROPERTY(VisibleDefaultsOnly, Category = "UI")
	UWidgetComponent* OverHeadWidgetComponent;

	/** Timer handle used to update overhead status gauge visibility. */
	FTimerHandle HeadStatGaugeVisibilityUpdateTimerHandle;

	/** Time interval between overhead status gauge visibility checks. */
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float HeadStatGaugeVisibilityCheckUpdateGap = 1.f;

	/** Squared distance threshold used to hide the overhead status gauge. */
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	float HeadStatGaugeVisibilityRangeSquared = 10000000.f;
};