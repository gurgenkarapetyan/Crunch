// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CAIController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/CCharacter.h"
#include "GAS/CAbilitySystemStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

ACAIController::ACAIController()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AI Perception Component");
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>("Sight Config");
	
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = false;
	
	SightConfig->SightRadius = 1000.f;
	SightConfig->LoseSightRadius = 1200.f;
	
	SightConfig->SetMaxAge(5.f);
	
	SightConfig->PeripheralVisionAngleDegrees = 180.f;
	
	AIPerceptionComponent->ConfigureSense(*SightConfig);
	
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ACAIController::TargetPerceptionUpdated);
	AIPerceptionComponent->OnTargetPerceptionForgotten.AddDynamic(this, &ACAIController::TargetForgotten);
}

void ACAIController::TargetPerceptionUpdated(AActor* TargetActor, const FAIStimulus Stimulus)
{
	if (Stimulus.WasSuccessfullySensed())
	{
		if (!GetCurrentTarget())
		{
			SetCurrentTarget(TargetActor);
		}
	}
	else
	{
		ForgetActorIfDead(TargetActor);
	}
}

const UObject* ACAIController::GetCurrentTarget() const
{
	if (const UBlackboardComponent* const BlackboardComponent = GetBlackboardComponent())
	{
		return GetBlackboardComponent()->GetValueAsObject(TargetBlackboardKeyName); 
	}
	
	return nullptr;
}

void ACAIController::SetCurrentTarget(AActor* NewTarget)
{
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	if (!BlackboardComponent)
	{
		return;
	}
	
	if (NewTarget)
	{
		BlackboardComponent->SetValueAsObject(TargetBlackboardKeyName, NewTarget);
	}
	else
	{
		 BlackboardComponent->ClearValue(TargetBlackboardKeyName);
	}
}

void ACAIController::TargetForgotten(AActor* ForgottenActor)
{
	if (!ForgottenActor)
	{
		return;
	}
	
	if (GetCurrentTarget() == ForgottenActor)
	{
		SetCurrentTarget(GetNextPerceivedActor());		
	}
}

AActor* ACAIController::GetNextPerceivedActor() const
{
	if (AIPerceptionComponent)
	{
		TArray<AActor*> PerceivedActors;
		AIPerceptionComponent->GetPerceivedHostileActors(PerceivedActors);
		
		if (PerceivedActors.Num() != 0)
		{
			return PerceivedActors[0];
		}
	}
	
	return nullptr;
}

void ACAIController::ForgetActorIfDead(AActor* ActorToForget) const
{
	const UAbilitySystemComponent* ActorASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(ActorToForget);
	if (ActorASC == nullptr)
	{
		return;
	}
	
	if (ActorASC->HasMatchingGameplayTag(UCAbilitySystemStatics::GetDeadStatTag()))
	{
		for (UAIPerceptionComponent::TActorPerceptionContainer::TIterator Iter = AIPerceptionComponent->GetPerceptualDataIterator(); Iter; ++Iter)
		{
			if (Iter->Key != ActorToForget)
			{
				continue;
			}
			
			for (FAIStimulus& Stimuli: Iter->Value.LastSensedStimuli)
			{
				Stimuli.SetStimulusAge(TNumericLimits<float>::Max());
			}
		}
	}
}

void ACAIController::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);
	
	SetGenericTeamId(FGenericTeamId(0));

	if (IGenericTeamAgentInterface* PawnTeamInterface = Cast<IGenericTeamAgentInterface>(NewPawn))
	{
		PawnTeamInterface->SetGenericTeamId(GetGenericTeamId());
	}
}

void ACAIController::BeginPlay()
{
	Super::BeginPlay();
	
	RunBehaviorTree(BehaviorTree);
}
