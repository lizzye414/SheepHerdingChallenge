// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SheepHerdChallenge/Scenery/EdgeWall.h"
#include "EngineUtils.h"
#include "SheepBaseCharacter.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "SheepAIController.generated.h"

/**
 * 
 */
UCLASS()
class SHEEPHERDCHALLENGE_API ASheepAIController : public AAIController
{
	GENERATED_BODY()

public:

	ASheepAIController();

	// Moves the sheep
	UFUNCTION()
	void MoveSheep();

	// Sets settings when the controller possesses the sheep
	UFUNCTION()
	virtual void OnPossess(APawn* InPawn) override;

	// Adds actors sensed to an array
	UFUNCTION()
	void SenseOthers(const TArray<AActor*>& ActorsFound);

	// Finds the location for the sheep to move to 
	UPROPERTY()
	FVector TargetLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Finds the closest edge wall to the sheep
	UFUNCTION()
	FVector FindClosestWall();

	// Finds all edge walls in the world
	UFUNCTION()
	void FindAllEdgeWalls();

	// Produces a random number
	UFUNCTION()
	float GetRandomNumber(float min, float max);

	// An array of all edge walls in the world
	UPROPERTY()
	TArray<AEdgeWall*> EdgeWalls;

	// Components to allow sensing other actors by sight
	UAIPerceptionComponent* PerceptionComponent;
	UAISenseConfig_Sight* SightConfig;
	
};
