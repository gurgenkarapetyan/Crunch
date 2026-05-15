// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MinionBarrack.h"

#include "SelectionSet.h"
#include "AI/CMinionCharacter.h"
#include "GameFramework/PlayerStart.h"

AMinionBarrack::AMinionBarrack()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMinionBarrack::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		GetWorldTimerManager().SetTimer(
			SpawnIntervalTimerHandle, 
			this, 
			&AMinionBarrack::SpawnNewGroup, 
			GroupSpawnInterval, 
			true
		);
	}
}

void AMinionBarrack::SpawnNewGroup()
{
	int i = MinionPerGroup;
	while (i > 0)
	{
		FTransform SpawnTransform = GetActorTransform();
		if (const APlayerStart* NextSpawnSpot = GetNextSpawnSpot())
		{
			SpawnTransform = NextSpawnSpot->GetActorTransform();
		}
		 
		ACMinionCharacter* const NextAvailableMinion = GetNextAvailableMinion();
		if (!NextAvailableMinion)
		{
			break;
		}
		
		NextAvailableMinion->SetActorTransform(SpawnTransform);
		NextAvailableMinion->Activate();
		--i;
	}
	
	SpawnNewMinions(i);
}

ACMinionCharacter* AMinionBarrack::GetNextAvailableMinion()
{
	for (ACMinionCharacter* Minion : MinionPool)
	{
		if (!Minion->IsActive())
		{
			return Minion;
		}
	}
	
	return nullptr;
}

void AMinionBarrack::SpawnNewMinions(const int Amount)
{
	for (int i = 0; i < Amount; i++)
	{
		FTransform SpawnTransform = GetActorTransform();
		if (const APlayerStart* NextSpawnSpot = GetNextSpawnSpot())
		{
			SpawnTransform = NextSpawnSpot->GetActorTransform();
		}
		
		ACMinionCharacter* NewMinion = GetWorld()->SpawnActorDeferred<ACMinionCharacter>(
			MinionClass, 
			SpawnTransform, 
			this, 
			nullptr,
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn
		);
		NewMinion->SetGenericTeamId(BarrackTeamID);
		NewMinion->FinishSpawning(SpawnTransform);
		NewMinion->SetGoal(Goal);
		MinionPool.Add(NewMinion);
	}
}

const APlayerStart* AMinionBarrack::GetNextSpawnSpot()
{
	if (SpawnSpots.Num() == 0)
	{
		return nullptr;
	}
	
	++NextSpawnSpotIndex;
	if (NextSpawnSpotIndex >= SpawnSpots.Num())
	{
		NextSpawnSpotIndex = 0;
	}
	
	return SpawnSpots[NextSpawnSpotIndex];
}

void AMinionBarrack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

