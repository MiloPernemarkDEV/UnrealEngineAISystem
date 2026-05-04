// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "DaAIConfig.h"
#include "EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREALAISYSTEM_API AEnemyBase : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta = (DisplayPriority = "1", AllowPrivateAccess = "true"))
	UDaAIConfig* AIConfigData = nullptr;
};
