// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "EnemyBase.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig.h"
#include "Engine/World.h"

AEnemyAIController::AEnemyAIController () {
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
	SetPerceptionComponent(*AIPerceptionComponent);
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (auto* EnemyBase = Cast<AEnemyBase>(InPawn))
	{
		SetGenericTeamId(EnemyBase->GetGenericTeamId());
		BehaviorTreesSetup(EnemyBase->AIConfigData);
		AIPerceptionSetup(EnemyBase->AIConfigData);
	}
}

ETeamAttitude::Type AEnemyAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	if (const auto* TeamAgent = Cast<IGenericTeamAgentInterface>(&Other))
	{
		FGenericTeamId OtherTeamId = TeamAgent->GetGenericTeamId();
		
		if (OtherTeamId == 255)
		{
			return ETeamAttitude::Neutral;
		}
		if (OtherTeamId == GetGenericTeamId())
		{
			return ETeamAttitude::Friendly;
		}
		if (OtherTeamId != GetGenericTeamId())
		{
			return ETeamAttitude::Hostile;
		}
	}
	return ETeamAttitude::Neutral;
}	

ETeamAttitude::Type AEnemyAIController::GetTeamAttitudeRelationship(const AActor* Other) const
{
	return GetTeamAttitudeTowards(*Other);
}

void AEnemyAIController::BehaviorTreesSetup(const UDaAIConfig* AIData)
{
	if (!IsValid(AIData) && !IsValid(AIData->BaseBehavior)) return;
	
	RunBehaviorTree(AIData->BaseBehavior);
	
	if (auto* BehaviorTreeComp	= FindComponentByClass<UBehaviorTreeComponent>())
	{
		for (const auto& Entry : AIData->DynamicBehaviors)
		{
			if (IsValid(Entry.BehaviorTree))
			{
				BehaviorTreeComp->SetDynamicSubtree(Entry.Tag, Entry.BehaviorTree);
			}
		}
	}
	
}

void AEnemyAIController::AIPerceptionSetup(const UDaAIConfig* AIData)
{
	
	if (!IsValid(AIPerceptionComponent) && !IsValid(AIData)) return;
	if (AIData->SenseConfigs.Num() <= 0) return;
	
	for (UAISenseConfig* SenseConfig : AIData->SenseConfigs)
	{
		if (IsValid(SenseConfig))
		{
			AIPerceptionComponent->ConfigureSense(*SenseConfig);
		}
	}
	
	if (auto* AIPerceptionSys = UAIPerceptionSystem::GetCurrent(GetWorld()))
	{
		AIPerceptionComponent->SetDominantSense(AIData->DominantSense);
	}
}

