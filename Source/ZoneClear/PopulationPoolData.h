// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PopulationPoolData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FWeightedPrefab {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> Prefab;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0"))
	float Weight = 1.0f;
};

UCLASS()
class ZONECLEAR_API UPopulationPoolData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Population")
	TArray<FWeightedPrefab> DecoyPrefabs;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Population")
	TSubclassOf<AActor> TargetPrefab;
	
};
