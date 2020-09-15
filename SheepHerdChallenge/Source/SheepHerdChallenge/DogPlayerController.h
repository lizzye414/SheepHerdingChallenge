// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Blueprint/UserWidget.h"
#include "DogPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHEEPHERDCHALLENGE_API ADogPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	virtual void BeginPlay() override;

	// The overall socre of the game so far
	UPROPERTY(EditAnywhere)
	float OverallScore;

	// Overall number of sheep penned in the game so far
	UPROPERTY(EditAnywhere)
	float OverallSheep;

public:
	ADogPlayerController();

	UFUNCTION()
	void SetUpdatedCurrentScore(float Score);

	UFUNCTION(BlueprintPure)
	float GetCurrentScore() const;

	UFUNCTION()
	void SetSheepCapturedInLevel(int NumSheep);

	UFUNCTION(BlueprintPure)
	float GetSheepCapturedInLevel() const;

	UFUNCTION()
	void EndLevel();

	UFUNCTION(BlueprintPure)
	int GetCurrentLevel() const;

	// Destroys sheep left in level, resets level and removes UI from screen
	UFUNCTION(BlueprintCallable)
	void NextLevel();

	UFUNCTION(BlueprintPure)
	float GetOverallScore();

	UFUNCTION(BlueprintPure)
	float GetOverallSheep();

	UPROPERTY(EditAnywhere)
	float CurrentScore;

protected:
	// Allows dog to be sensed by sheep by sight
	UAISenseConfig_Sight* SightConfig;

	UPROPERTY(EditAnywhere, Category = "HUD Elements")
	TSubclassOf<UUserWidget> EndLevelWidgetClass;

	UPROPERTY()
	UUserWidget* EndLevelWidget;

	UPROPERTY(EditAnywhere)
	int SheepCapturedInLevel = 0;

	UPROPERTY()
	int CurrentLevel = 1;

};
