// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "WinTriggerVolume.generated.h"

/**
 * 
 */
UCLASS()
class SHEEPHERDCHALLENGE_API AWinTriggerVolume : public ATriggerVolume
{
	GENERATED_BODY()

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// declare overlap begin function
	UFUNCTION()
		void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	// declare overlap end function
	UFUNCTION()
		void OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);
	
};
