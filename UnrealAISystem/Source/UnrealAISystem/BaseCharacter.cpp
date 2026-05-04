// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"

// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

FGenericTeamId ABaseCharacter::GetGenericTeamId() const
{
	return TeamID;
}
 
bool ABaseCharacter::CanBeSeenOverride_Implementation()
{
	return true;
}
 
UAISense_Sight::EVisibilityResult ABaseCharacter::CanBeSeenFrom(const FCanBeSeenFromContext& Context, FVector& OutSeenLocation, int32& OutNumberOfLoSChecksPerformed, int32& OutNumberOfAsyncLosCheckRequested, float& OutSightStrength, int32* UserData, const FOnPendingVisibilityQueryProcessedDelegate* Delegate)
{
	if (!CanBeSeenOverride())
	{
		return UAISense_Sight::EVisibilityResult::NotVisible;
	}
 
 
	// From AISense_Sight.cpp ln 567
	FHitResult HitResult;
	const auto& TargetLocation = GetActorLocation();
	const auto& DefaultSightCollisionChannel = GET_AI_CONFIG_VAR(DefaultSightCollisionChannel);
	const FCollisionQueryParams QueryParams = FCollisionQueryParams(SCENE_QUERY_STAT(AILineOfSight), true, Context.IgnoreActor);
	const bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, Context.ObserverLocation, TargetLocation, DefaultSightCollisionChannel, QueryParams, FCollisionResponseParams::DefaultResponseParam);
 
	++OutNumberOfLoSChecksPerformed;
 
	const auto IsTraceConsideredVisible = [](const FHitResult& HitResult, const AActor* TargetActor)
	{
		const AActor* HitResultActor = HitResult.HitObjectHandle.FetchActor();
		return (HitResultActor ? HitResultActor->IsOwnedBy(TargetActor) : false);
	};
 
	if (!bHit || IsTraceConsideredVisible(HitResult, this))
	{
		OutSeenLocation = TargetLocation;
		return UAISense_Sight::EVisibilityResult::Visible;
	}
 
	return UAISense_Sight::EVisibilityResult::NotVisible;
}

