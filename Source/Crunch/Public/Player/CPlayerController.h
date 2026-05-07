// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CPlayerController.generated.h"

class UGameplayWidget;
class ACPlayerCharacter;
/**
 * 
 */
UCLASS()
class CRUNCH_API ACPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// only called on the server
	virtual void OnPossess(APawn* NewPawn) override;
	
	// only called on the client, also on the listening server
	virtual void AcknowledgePossession(APawn* NewPawn) override;
	
private:
	void SpawnGameplayWidget();
	
private:
	UPROPERTY()
	ACPlayerCharacter* CPlayerCharacter;
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UGameplayWidget> GameplayWidgetClass;
	
	UPROPERTY()
	UGameplayWidget* GameplayWidget;
};
