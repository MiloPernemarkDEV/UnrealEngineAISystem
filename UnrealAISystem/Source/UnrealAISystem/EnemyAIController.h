// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GenericTeamAgentInterface.h"
#include "DaAIConfig.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALAISYSTEM_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEnemyAIController();
	
	ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;
	
	UFUNCTION(BlueprintCallable, Category = "Team")
	ETeamAttitude::Type GetTeamAttitudeRelationship(const AActor* other) const;
	
protected:
	virtual void OnPossess(APawn* InPawn) override;
	
private:
	void BehaviorTreesSetup(const UDaAIConfig* AIData);
	
	void AIPerceptionSetup(const UDaAIConfig* AIData);
};
