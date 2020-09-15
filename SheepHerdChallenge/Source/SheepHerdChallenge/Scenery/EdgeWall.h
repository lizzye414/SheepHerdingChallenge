// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "EdgeWall.generated.h"

UCLASS()
class SHEEPHERDCHALLENGE_API AEdgeWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEdgeWall();

	// To set actor static mesh
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* WallSM;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
