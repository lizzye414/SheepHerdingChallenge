// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "Components/InputComponent.h"
#include "DogPawn.generated.h"

/**
 * 
 */
UCLASS()
class SHEEPHERDCHALLENGE_API ADogPawn : public ADefaultPawn
{
	GENERATED_BODY()

public:

	void BeginPlay() override;

	// The base speed of the dog
	UPROPERTY(EditAnywhere, Category = "Settings")
	float DogSpeed = 1.0f;


private:

	void MoveUp(float Value);

	void MoveRight(float Value);

	// End the level and show current score
	void EndLevel();

protected:

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
};
