#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BehaviorTree/BehaviorTree.h"
#include "DaAIConfig.generated.h"

class UAISenseConfig;
class UAISense;

USTRUCT(BlueprintType)
struct UNREALAISYSTEM_API FTaggedBehaviorTree
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag Tag;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UBehaviorTree* BehaviorTree = nullptr; 
};

UCLASS(BlueprintType)
class UNREALAISYSTEM_API UDaAIConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseLogic")
	UBehaviorTree* BaseBehavior = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StateLogic")
	TArray<FTaggedBehaviorTree> DynamicBehaviors;
	
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category = "AI Perception")
	TArray<TObjectPtr<UAISenseConfig>> SenseConfigs;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI Perception")
	TSubclassOf<UAISense> DominantSense;
};
