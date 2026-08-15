// Fill out your copyright notice in the Description page of Project Settings.


#include "ZoneMarkerActor.h"

// Sets default values
AZoneMarkerActor::AZoneMarkerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AZoneMarkerActor::Populate()
{
    ClearPopulation();

    if (!Pool || SpawnPoints.Num() == 0) return;

    int32 TargetIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);

    for (int32 i = 0; i < SpawnPoints.Num(); i++)
    {
        if (!SpawnPoints[i]) continue;

        bool bIsTarget = (i == TargetIndex);
        TSubclassOf<AActor> PrefabClass = bIsTarget
            ? Pool->TargetPrefab
            : GetWeightedDecoy();

        if (!PrefabClass) continue;

        FVector SpawnLocation = SpawnPoints[i]->GetActorLocation();
        FRotator SpawnRotation = SpawnPoints[i]->GetActorRotation();

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;

        AActor* Spawned = GetWorld()->SpawnActor<AActor>(
            PrefabClass,
            SpawnLocation,
            SpawnRotation,
            SpawnParams
        );

        if (Spawned)
        {
            SpawnedInstances.Add(Spawned);
        }
    }
}

void AZoneMarkerActor::ClearPopulation()
{
	for (AActor* Instance : SpawnedInstances)
	{
		if (Instance)
		{
			Instance->Destroy();
		}
	}
	SpawnedInstances.Empty();
}

void AZoneMarkerActor::OnTargetFound()
{
	if (bResolved) return;
	bResolved = true;
	UE_LOG(LogTemp, Warning, TEXT("Target found! Zone resolved."));
}

TSubclassOf<AActor> AZoneMarkerActor::GetWeightedDecoy()
{
	if (Pool->DecoyPrefabs.Num() == 0) return nullptr;

	float TotalWeight = 0.0f;
	for (const FWeightedPrefab& Entry : Pool->DecoyPrefabs) {
		TotalWeight += Entry.Weight;
	}

	float Roll = FMath::FRandRange(0.0f, TotalWeight);
	float Accumulated = 0.0f;

	for (const FWeightedPrefab& Entry : Pool->DecoyPrefabs)
	{
		Accumulated += Entry.Weight;
		if(Roll <= Accumulated)
		{
			return Entry.Prefab;
		}
	}

	return Pool->DecoyPrefabs.Last().Prefab;

}



// Called when the game starts or when spawned
void AZoneMarkerActor::BeginPlay()
{
	Super::BeginPlay();
	Populate();
	
}

// Called every frame
void AZoneMarkerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

