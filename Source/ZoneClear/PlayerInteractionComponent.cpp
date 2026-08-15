// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInteractionComponent.h"
#include "InteractableComponent.h"
#include "ZoneMarkerActor.h"

// Sets default values for this component's properties
UPlayerInteractionComponent::UPlayerInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UPlayerInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame


