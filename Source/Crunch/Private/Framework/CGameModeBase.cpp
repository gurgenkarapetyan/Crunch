// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/CGameModeBase.h"

#include "EngineUtils.h"
#include "GameFramework/PlayerStart.h"

APlayerController* ACGameModeBase::SpawnPlayerController(ENetRole InRemoteRole, const FString& Options)
{
	APlayerController* NewPlayerController = Super::SpawnPlayerController(InRemoteRole, Options);
	const FGenericTeamId TeamId = GetTeamIDForPlayer(NewPlayerController);
	if (IGenericTeamAgentInterface* NewPlayerTeamInterface = Cast<IGenericTeamAgentInterface>(NewPlayerController))
	{
		NewPlayerTeamInterface->SetGenericTeamId(TeamId);
	}
	
	NewPlayerController->StartSpot = FindNextStartSpotForTeam(TeamId);
	return NewPlayerController;
}

FGenericTeamId ACGameModeBase::GetTeamIDForPlayer(const APlayerController* PlayerController) const
{
	static int PlayerCount = 0;
	++PlayerCount;
	
	return FGenericTeamId(PlayerCount % 2);
}

AActor* ACGameModeBase::FindNextStartSpotForTeam(const FGenericTeamId& TeamID) const
{
	const FName* StartSpotTag = TeamStartSpotTagMap.Find(TeamID);
	if (!StartSpotTag)
	{
		return nullptr;
	}

	const UWorld* World = GetWorld();
	for (TActorIterator<APlayerStart> It(World); It; ++It)
	{
		if (It->PlayerStartTag == *StartSpotTag)
		{
			It->PlayerStartTag = FName("Taken");
			return *It;
		}
	}
	
	return nullptr;
}
