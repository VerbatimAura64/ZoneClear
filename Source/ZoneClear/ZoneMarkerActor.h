// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TargetPoint.h"
#include "PopulationPoolData.h"
#include "ZoneMarkerActor.generated.h"

UCLASS()
class ZONECLEAR_API AZoneMarkerActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZoneMarkerActor();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zone")
	UPopulationPoolData* Pool;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zone")
	TArray<ATargetPoint*> SpawnPoints;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Zone", meta = (ClampMin = "0.0", ClampMax = "1.0"))
		float CamouflageTightness = 0.2f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Zone")
	bool bResolved = false;

	UFUNCTION(BlueprintCallable, Category = "Zone")
	void Populate();

	UFUNCTION(BlueprintCallable, Category = "Zone")
	void ClearPopulation();

private:
	UPROPERTY()
	TArray<AActor*> SpawnedInstances;
	TSubclassOf<AActor> GetWeightedDecoy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
