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
	void SpawnNewMinions(const int Amount);
	
	const APlayerStart* GetNextSpawnSpot();
	
	void SpawnNewGroup();
	
	ACMinionCharacter* GetNextAvailableMinion();
	
private:
	UPROPERTY(EditAnywhere, Category = "Spawn")
	FGenericTeamId BarrackTeamID;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	int MinionPerGroup = 3;
	
	UPROPERTY(EditAnywhere, Category = "Spawn")
	float GroupSpawnInterval = 5.f;
	
	UPROPERTY()
	TArray<ACMinionCharacter*> MinionPool;
	
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TSubclassOf<ACMinionCharacter> MinionClass;
	
	UPROPERTY(EditAnywhere, Category = "Spawn")
	TArray<APlayerStart*> SpawnSpots;
	
	int NextSpawnSpotIndex = -1;
	
	FTimerHandle SpawnIntervalTimerHandle;
};
