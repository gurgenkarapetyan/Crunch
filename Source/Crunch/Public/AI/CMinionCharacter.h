// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CCharacter.h"
#include "CMinionCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CRUNCH_API ACMinionCharacter : public ACCharacter
{
	GENERATED_BODY()
	
public:
	/**
	 * @brief Updates the minion team ID and refreshes team-based visuals.
	 *
	 * @param NewTeamID New team identifier.
	 */
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;
	
	/**
	 * @brief Returns whether this minion is currently active.
	 *
	 * A minion is considered active when it is not dead.
	 *
	 * @return True if the minion is active.
	 */
	bool IsActive() const;
	
	/**
	 * @brief Reactivates the minion from the pooled dead state.
	 */
	void Activate() const;
	
	/**
	 * @brief Assigns the goal actor used by the AI blackboard.
	 *
	 * @param Goal Goal actor assigned to the minion AI.
	 */
	void SetGoal(AActor* Goal) const;
	
private:
	/**
	 * @brief Selects the skeletal mesh based on the current team ID.
	 */
	void PickSkinBasesOnTeamID();
	
	/**
	 * @brief Called when the replicated team ID changes.
	 *
	 * Updates the minion visual appearance.
	 */
	virtual void OnRep_TeamID() override;
	
private:
	/** Blackboard key name used to store the current AI goal actor. */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName GoalBlackboardKeyName = "Goal";
	
	/** Skeletal meshes mapped to team identifiers. */
	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	TMap<FGenericTeamId, USkeletalMesh*> SkinMap;
};
