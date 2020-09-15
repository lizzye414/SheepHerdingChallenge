// Fill out your copyright notice in the Description page of Project Settings.


#include "EdgeWall.h"

// Sets default values
AEdgeWall::AEdgeWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WallSM = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallSM"));
	WallSM->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEdgeWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEdgeWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

