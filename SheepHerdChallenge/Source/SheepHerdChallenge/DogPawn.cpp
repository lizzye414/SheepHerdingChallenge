// Fill out your copyright notice in the Description page of Project Settings.


#include "DogPawn.h"
#include "DogPlayerController.h"


void ADogPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ADogPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{

	check(InputComponent);

	// Bind movement events and actions
	PlayerInputComponent->BindAxis("MoveUp", this, &ADogPawn::MoveUp);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADogPawn::MoveRight);

	PlayerInputComponent->BindAction("EndLevel", IE_Pressed, this, &ADogPawn::EndLevel);

}

void ADogPawn::MoveUp(float Value)
{

	if (Value != 0.0f)
	{
		// add movement in up/down direction
		AddMovementInput(GetActorForwardVector(), (Value * DogSpeed));
	}

}

void ADogPawn::MoveRight(float Value)
{

	if (Value != 0.0f)
	{
		// add movement in left/right direction
		AddMovementInput(GetActorRightVector(), (Value * DogSpeed));
	}

}

void ADogPawn::EndLevel()
{
	// Displays the end of level UI
	ADogPlayerController* DogCon = Cast<ADogPlayerController>(GetController());
	DogCon->EndLevel();
}