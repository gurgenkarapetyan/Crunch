// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CCharacter.h"
#include "CPlayerCharacter.generated.h"

enum class ECAbilityInputID : uint8;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class CRUNCH_API ACPlayerCharacter : public ACCharacter
{
	GENERATED_BODY()
	
public:

	/**
	 * @brief Sets up camera components and character movement rotation settings.
	 */
	ACPlayerCharacter();

	/**
	 * @brief Reinitializes local player input mapping when the pawn is restarted on the client.
	 */
	virtual void PawnClientRestart() override;

	/**
	 * @brief Binds player input actions for movement, looking, jumping, and gameplay abilities.
	 * @param PlayerInputComponent Input component used to bind actions.
	 */
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
private:

	/**
	 * @brief Handles camera look input.
	 * @param InputActionValue Input value containing look axis data.
	 */
	void HandleLookInput(const FInputActionValue& InputActionValue);

	/**
	 * @brief Handles character movement input relative to the camera direction.
	 * @param InputActionValue Input value containing movement axis data.
	 */
	void HandleMoveInput(const FInputActionValue& InputActionValue);

	/**
	 * @brief Forwards ability input press and release events to the Ability System Component.
	 * @param InputActionValue Input value containing pressed state.
	 * @param InputID Ability input identifier associated with the input action.
	 */
	void HandleAbilityInput(const FInputActionValue& InputActionValue, ECAbilityInputID InputID);

	/**
	 * @brief Returns the camera right direction.
	 * @return Right vector of the view camera.
	 */
	FVector GetLookRightDirection() const;

	/**
	 * @brief Returns the camera forward direction.
	 * @return Forward vector of the view camera.
	 */
	FVector GetLookForwardDirection() const;

	/**
	 * @brief Returns the flattened forward movement direction based on the camera right vector.
	 * @return World-space movement forward direction.
	 */
	FVector GetMoveForwardDirection() const;
	
private:

	/** Spring arm used to position the player camera. */
	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	USpringArmComponent* CameraBoom;

	/** Camera used as the player view. */
	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	UCameraComponent* ViewCamera;
	
	/*****************************************************************************/
	/**									Input									 */
	/*************************************************************************** */

	/** Mapping context added to the local player for gameplay input. */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* GameplayInputMappingContext;

	/** Input action used for jumping. */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* JumpInputAction;

	/** Input action used for camera look input. */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookInputAction;

	/** Input action used for character movement input. */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveInputAction;

	/** Input actions mapped to gameplay ability input IDs. */
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TMap<ECAbilityInputID, UInputAction*> GameplayAbilityInputActions;
};