// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "CCharacter.generated.h"

class UAIPerceptionStimuliSourceComponent;
struct FGameplayTag;
class UWidgetComponent;
class UCAttributeSet;
class UCAbilitySystemComponent;

UCLASS()
class CRUNCH_API ACCharacter : public ACharacter, public IAbilitySystemInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	ACCharacter();

	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
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
	
	/**
	 * @brief Called when the character enters the dead state.
	 *
	 * Intended to be overridden by child classes for custom death behavior.
	 */
	virtual void OnDead();

	/**
	 * @brief Called when the character respawns.
	 *
	 * Intended to be overridden by child classes for custom respawn behavior.
	 */
	virtual void OnRespawn();
	
private:
	/**
	 * @brief Registers gameplay tag change delegates on the Ability System Component.
	 */
	void BindGASChangeDelegate();
	
	/**
	 * @brief Called when the dead gameplay tag count changes.
	 *
	 * Starts the death sequence when the tag is added and respawns when removed.
	 *
	 * @param Tag Gameplay tag that changed.
	 * @param NewCount New active tag count.
	 */
	void DeathTagUpdated(const FGameplayTag Tag, int32 NewCount);
	
	/**
	 * @brief Starts the full death sequence.
	 *
	 * Disables movement, collision, status UI, and plays the death animation.
	 */
	void StartDeathSequence();
	
	/**
	 * @brief Respawns the character and restores gameplay state.
	 */
	void Respawn();
	
	/**
	 * @brief Plays the configured death montage.
	 */
	void PlayDeathAnimation();
	
	/**
	 * @brief Called when the death montage sequence has finished.
	 */
	void DeathMontageFinished() const;
	
	/**
	 * @brief Enables or disables ragdoll simulation on the character mesh.
	 *
	 * @param bIsEnabled True to enable ragdoll simulation.
	 */
	void SetRagdollEnabled(const bool bIsEnabled) const;

private:
	/** Ability System Component used to manage abilities, effects, tags, and gameplay cues. */
	UPROPERTY(VisibleDefaultsOnly, Category = "Gameplay Ability")
	UCAbilitySystemComponent* CAbilitySystemComponent;

	/** Attribute Set containing this character's gameplay attributes. */
	UPROPERTY()
	UCAttributeSet* CAttributeSet;
	
	/** Death montage played when the character dies. */
	UPROPERTY(EditDefaultsOnly, Category = "Death")
	UAnimMontage* DeathMontage = nullptr;
	
	/**
	 * @brief Time offset applied to the death montage duration before ragdoll activation.
	 *
	 * Negative values trigger ragdoll before the montage fully finishes.
	 */
	UPROPERTY(EditDefaultsOnly, Category = "Death")
	float DeathMontageFinishTimeShift = -0.8f;
	
	/** Timer handle used to trigger post-death montage logic. */
	FTimerHandle DeathMontageTimerHandle;
	
	/** Cached mesh relative transform used to restore mesh position after ragdoll. */
	FTransform MeshRelativeTransform;
	
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

	/**
	 * @brief Enables or disables the overhead status gauge widget.
	 *
	 * @param bIsEnabled True to enable the status gauge.
	 */
	void SetStatusGaugeEnabled(const bool bIsEnabled); 
	
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
	
	/*****************************************************************************/
	/**								     Team							         */
	/*************************************************************************** */
public:
	/** Assigns Team Agent to given TeamID */
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override; 
	
	/** Retrieve team identifier in form of FGenericTeamId */
	virtual FGenericTeamId GetGenericTeamId() const override { return TeamID; }
	
private:
	UPROPERTY(ReplicatedUsing = OnRep_TeamID)
	FGenericTeamId TeamID;
	
	UFUNCTION()
	virtual void OnRep_TeamID() { /** override in child class */ };
	
	/*****************************************************************************/
	/**								     AI							             */
	/*************************************************************************** */
private:
	void SetAIPerceptionStimuliSourceEnabled(bool bIsEnabled);
	
	UPROPERTY()
	UAIPerceptionStimuliSourceComponent* PerceptionStimuliSourceComponent;
};