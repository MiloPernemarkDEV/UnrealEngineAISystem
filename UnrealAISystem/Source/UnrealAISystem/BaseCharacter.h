// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "Perception/AISightTargetInterface.h"
#include "Perception/AIPerceptionSystem.h"
#include "BaseCharacter.generated.h"

UCLASS()
class UNREALAISYSTEM_API ABaseCharacter : public ACharacter, public IGenericTeamAgentInterface, public IAISightTargetInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
 
	//IGenericTeamAgentInterface
	virtual FGenericTeamId GetGenericTeamId() const override;
 
	UFUNCTION(BlueprintNativeEvent)
	bool CanBeSeenOverride();
 
	bool CanBeSeenOverride_Implementation();
 
	//IAISightTargetInterface
	virtual UAISense_Sight::EVisibilityResult CanBeSeenFrom(const FCanBeSeenFromContext& Context,
		FVector& OutSeenLocation, int32& OutNumberOfLoSChecksPerformed, 
		int32& OutNumberOfAsyncLosCheckRequested, float& OutSightStrength, 
		int32* UserData = nullptr, const FOnPendingVisibilityQueryProcessedDelegate* Delegate = nullptr) override;
 
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
 
	//TeamId
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Team")
	FGenericTeamId TeamID = FGenericTeamId(255);
};