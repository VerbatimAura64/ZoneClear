// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInteractionComponent.h"
#include "InteractableComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "ZoneMarkerActor.h"

// Sets default values for this component's properties
UPlayerInteractionComponent::UPlayerInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UPlayerInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	// ...

}

void UPlayerInteractionComponent::TryInteract()
{
	if (!PlayerController) return;
	APlayerCameraManager* CameraManager = PlayerController->PlayerCameraManager;

	if (!CameraManager) return;

	FVector Start = CameraManager->GetCameraLocation();
	FVector End = Start + (CameraManager->GetCameraRotation().Vector() * InteractRange);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	AActor* Owner = GetOwner();
	if(Owner && Owner->IsValidLowLevel())
	{
		Params.AddIgnoredActor(Owner);
	}


	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_Visibility,
		Params
	);

	if(bHit && HitResult.GetActor())
	{
		UInteractableComponent* Interactable = HitResult.GetActor()->FindComponentByClass<UInteractableComponent>();
		if (Interactable)
		{
			Interactable->OnInteract();
			if (Interactable->bIsTarget && Interactable->OwnerZone) {
				OnFragmentReceived.Broadcast(Interactable->OwnerZone->FragmentText);
			}
		}
	}
	DrawDebugLine(GetWorld(), Start, bHit ? HitResult.ImpactPoint : End,  FColor::Red, false, 15.0f);
	UE_LOG(LogTemp, Warning, TEXT("Line trace - Hit: %s, Location: %s"),
		bHit ? TEXT("YES") : TEXT("NO"),
		bHit ? *HitResult.GetActor()->GetName() : TEXT("Nothing"));
}


// Called when the game starts


// Called every frame


