// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenericTeamAgentInterface.h"
#include "MinionBarrack.generated.h"

class ACMinionCharacter;

UCLASS()
class CRUNCH_API AMinionBarrack : public AActor
{
	GENERATED_BODY()
	
public:	
	AMinionBarrack();

	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
	
private:
	/**
	 * @brief Spawns a specified number of new minions.
	 *
	 * @param Amount Number of minions to spawn.
	 */
	void SpawnNewMinions(const int Amount);
	
	/**
	 * @brief Returns the next spawn location from the configured spawn spot list.
	 *
	 * Cycles through spawn spots sequentially.
	 *
	 * @return Next spawn spot actor, or nullptr if none exist.
	 */
	const APlayerStart* GetNextSpawnSpot();
	
	/**
	 * @brief Spawns or reactivates a full minion group.
	 */
	void SpawnNewGroup();
	
	/**
	 * @brief Returns the next inactive minion from the object pool.
	 *
	 * @return Available pooled minion, or nullptr if none are available.
	 */
	ACMinionCharacter* GetNextAvailableMinion();
	
private:
	/** Team identifier assigned to newly spawned minions. */
	UPROPERTY(EditAnywhere, Category = "Spawn")
	FGenericTeamId BarrackTeamID;

	/** Number of minions spawned in each group. */
	UPROPERTY(EditAnywhere, Category = "Spawn")
	int MinionPerGroup = 3;
	
	/** Time interval between minion group spawns. */
	UPROPERTY(EditAnywhere, Category = "Spawn")
	float GroupSpawnInterval = 5.f;
	
	UPROPERTY()
	TArray<ACMinionCharacter*> MinionPool;

	/** Goal actor assigned to spawned minions. */
	UPROPERTY(EditAnywhere, Category = "Spawn")
	AActor* Goal;
	
	/** Minion class spawned by this barrack. */
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<ACMinionCharacter> MinionClass;
	
	/** Spawn locations used when spawning minion groups. */
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TArray<APlayerStart*> SpawnSpots;
	
	/** Current spawn spot index used for round-robin spawn selection. */
	int NextSpawnSpotIndex = -1;
	
	/** Timer handle used for periodic group spawning. */
	FTimerHandle SpawnIntervalTimerHandle;
};
