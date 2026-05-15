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
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;
	
	bool IsActive() const;
	void Activate() const;
	
private:
	void PickSkinBasesOnTeamID();
	
	virtual void OnRep_TeamID() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	TMap<FGenericTeamId, USkeletalMesh*> SkinMap;
};
