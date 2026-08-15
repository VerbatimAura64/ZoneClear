// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractableComponent.generated.h"

class AZoneMarkerActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ZONECLEAR_API UInteractableComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractableComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	bool bIsTarget = false;

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void OnInteract();

	UPROPERTY(BlueprintReadOnly, Category = "Interaction")
	AZoneMarkerActor* OwnerZone;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
