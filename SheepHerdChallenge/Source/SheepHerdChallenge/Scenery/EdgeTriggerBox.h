// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "EdgeTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class SHEEPHERDCHALLENGE_API AEdgeTriggerBox : public ATriggerBox
{
	GENERATED_BODY()

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// constructor sets default values for this actor's properties
	AEdgeTriggerBox();

	// declare overlap begin function
	UFUNCTION()
	void OnOverlap(AActor* OverlappedActor, AActor* OtherActor);
	
};
