// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CAIController.generated.h"

struct FAIStimulus;
class UAISenseConfig_Sight;

/**
 * 
 */
UCLASS()
class CRUNCH_API ACAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ACAIController();
	
	virtual void OnPossess(APawn* NewPawn) override;
	
	virtual void BeginPlay() override;
	
private:
	/**
	 * @brief Called when perception state changes for a target actor.
	 *
	 * Updates the current target when actors become sensed or lost.
	 *
	 * @param TargetActor Actor whose perception state changed.
	 * @param Stimulus Perception stimulus information.
	 */
	UFUNCTION()
	void TargetPerceptionUpdated(AActor* TargetActor, FAIStimulus Stimulus);
	
	/**
	 * @brief Called when a perceived actor is completely forgotten by perception.
	 *
	 * @param ForgottenActor Actor no longer remembered by perception.
	 */
	UFUNCTION()
	void TargetForgotten(AActor* ForgottenActor);
	
	/**
	 * @brief Returns the currently assigned target from the blackboard.
	 * @return Current target object stored in the blackboard.
	 */
	const UObject* GetCurrentTarget() const;
	
	/**
	 * @brief Updates the current blackboard target.
	 *
	 * Clears the target if nullptr is provided.
	 *
	 * @param NewTarget New target actor to assign.
	 */
	void SetCurrentTarget(AActor* NewTarget);
	
	/**
	 * @brief Returns the next perceived hostile actor.
	 * @return First currently perceived hostile actor, or nullptr if none exist.
	 */
	AActor* GetNextPerceivedActor() const;
	
	void ForgetActorIfDead(AActor* ActorToForget) const;
	
private:
	/** Behavior tree executed by this AI controller. */
	UPROPERTY(EditDefaultsOnly, Category = "AI Behavior")
	UBehaviorTree* BehaviorTree = nullptr;
	
	/** Blackboard key name used to store the current target actor. */
	UPROPERTY(EditDefaultsOnly, Category = "AI Behavior")
	FName TargetBlackboardKeyName = "Target";
	
	/** AI perception component responsible for sensing nearby actors. */
	UPROPERTY(VisibleDefaultsOnly, Category = "Perception")
	UAIPerceptionComponent* AIPerceptionComponent;
	
	/** Sight perception configuration used by the AI perception component. */
	UPROPERTY(VisibleDefaultsOnly, Category = "Perception")
	UAISenseConfig_Sight* SightConfig;
};
