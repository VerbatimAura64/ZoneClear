#pragma once
// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFragText, FText, Text);
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ZONECLEAR_API UPlayerInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlayerInteractionComponent();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction")
	float InteractRange = 1000.0f;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FFragText OnFragmentReceived;
	
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void TryInteract();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	APlayerController* PlayerController;
};
