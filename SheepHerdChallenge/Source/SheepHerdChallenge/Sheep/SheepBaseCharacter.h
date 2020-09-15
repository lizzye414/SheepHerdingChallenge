// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "SheepBaseCharacter.generated.h"

UCLASS()
class SHEEPHERDCHALLENGE_API ASheepBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	// Class variable to allocate unique IDs
	static int ID;

	// Sets default values for this character's properties
	ASheepBaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// The base speed of the sheep
	UPROPERTY()
	float MaxSpeed = 50.0f;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Destroys the controller and sheep
	UFUNCTION()
	void DestroySelf();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	// Sets speed of sheep based on level
	UFUNCTION()
		void SetMaxSpeed(int Level);

	// Points awarded when this sheep is penned
	UPROPERTY(EditAnywhere)
	float WinPoints = 10;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Sheep;

	// How far away the sheep can sense other actors
	UPROPERTY(EditAnywhere, Category = "Settings")
	float SightRange = 70.0f;

};
