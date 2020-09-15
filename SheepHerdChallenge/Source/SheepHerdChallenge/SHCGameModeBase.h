// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SheepHerdChallenge/Sheep/SheepBaseCharacter.h"
#include "SHCGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHEEPHERDCHALLENGE_API ASHCGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	float GetRandomLocation(float min, float max);

	UPROPERTY(EditAnywhere)
	float TotalScore;

	UPROPERTY(EditAnywhere)
	float TotalSheep;


public:

	UFUNCTION()
	void SetUpLevel(int Level);

	UFUNCTION()
	void RecordScore(float Score, float NumSheep);

	UFUNCTION(BlueprintPure)
	float GetTotalScore();

	UFUNCTION(BlueprintPure)
	float GetTotalSheep();
	
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<ASheepBaseCharacter> SheepToSpawn;
};
