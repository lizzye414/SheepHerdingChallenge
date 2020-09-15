// Fill out your copyright notice in the Description page of Project Settings.


#include "SHCGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include <random>

void ASHCGameModeBase::BeginPlay()
{

	Super::BeginPlay();

	SetUpLevel(1);

	TotalScore = 0;

	TotalSheep = 0;

}

float ASHCGameModeBase::GetRandomLocation(float min, float max)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	static std::uniform_real_distribution<float> dis(min, max);

	return dis(rd);
}

void ASHCGameModeBase::SetUpLevel(int Level)
{

	FActorSpawnParameters SpawnParameters;
	UWorld* World = GetWorld();

	// Spawns sheep at random location, number of sheep based on level 
	for (int i = 0; i < (10 + Level); i++)
	{

		float LocX = GetRandomLocation(-250.0f, 250.0f);
		float LocY = GetRandomLocation(-480.0f, 471.0f);

		ACharacter* Spawned = World->SpawnActor<ASheepBaseCharacter>(ASheepBaseCharacter::StaticClass(), (FVector(LocX, LocY, 36.0f)), FRotator::ZeroRotator, SpawnParameters);

	}

}

void ASHCGameModeBase::RecordScore(float Score, float NumSheep)
{

	TotalScore = TotalScore + Score;
	TotalSheep = TotalSheep + NumSheep;

}

float ASHCGameModeBase::GetTotalScore()
{

	return TotalScore;

}

float ASHCGameModeBase::GetTotalSheep()
{
	return TotalSheep;
}
