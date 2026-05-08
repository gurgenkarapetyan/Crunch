// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

class UGameplayWidget;
class ACPlayerCharacter;

UCLASS()
class CRUNCH_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	/**
	 * @brief Called on the server when this controller possesses a pawn.
	 * @param NewPawn Pawn possessed by this controller.
	 */
	virtual void OnPossess(APawn* NewPawn) override;

	/**
	 * @brief Called on the owning client when possession is acknowledged.
	 *
	 * Also called on a listen server for the local player.
	 *
	 * @param NewPawn Pawn possessed by this controller.
	 */
	virtual void AcknowledgePossession(APawn* NewPawn) override;
	
private:

	/**
	 * @brief Creates and adds the gameplay widget to the local player's viewport.
	 */
	void SpawnGameplayWidget();
	
private:

	/** Cached player character possessed by this controller. */
	UPROPERTY()
	ACPlayerCharacter* CPlayerCharacter;

	/** Gameplay widget class used to create the player's HUD. */
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UGameplayWidget> GameplayWidgetClass;

	/** Runtime gameplay widget instance added to the viewport. */
	UPROPERTY()
	UGameplayWidget* GameplayWidget;
};