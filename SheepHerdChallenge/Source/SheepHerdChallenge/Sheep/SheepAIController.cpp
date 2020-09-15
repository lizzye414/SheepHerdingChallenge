// Fill out your copyright notice in the Description page of Project Settings.


#include "SheepAIController.h"
#include "Math/Vector.h"
#include "Kismet/GameplayStatics.h"
#include <random>
#include <time.h>
#include "SheepHerdChallenge/DogPawn.h"

ASheepAIController::ASheepAIController()
{
	// Allows sheep to see other actors
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &ASheepAIController::SenseOthers);

	// Allows other sheep to see this sheep
	UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, SightConfig->GetSenseImplementation(), GetPawn());
}

void ASheepAIController::OnPossess(APawn* InPawn)
{

	Super::OnPossess(InPawn);

	FindAllEdgeWalls();

	MoveSheep();
	
	ASheepBaseCharacter* PossessedSheep = Cast<ASheepBaseCharacter>(GetPawn());

	// Sets parameters to sensing other actors
	SightConfig->SightRadius = PossessedSheep->SightRange;
	SightConfig->LoseSightRadius = (PossessedSheep->SightRange + 20.0f);
	SightConfig->PeripheralVisionAngleDegrees = 360.0f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	PerceptionComponent->ConfigureSense(*SightConfig);

}

void ASheepAIController::SenseOthers(const TArray<AActor*>& ActorsFound)
{

	int CurrentID = 100000;

	ASheepBaseCharacter* SheepToFollow = nullptr;

	for (AActor* EachActor : ActorsFound)
	{
		// If the sensed actor is a sheep, follow it if it has a lower ID than this sheep
		if (EachActor->GetClass()->IsChildOf(ASheepBaseCharacter::StaticClass()))
		{
			ASheepBaseCharacter* EachCharacter = Cast<ASheepBaseCharacter>(EachActor);
			if (EachCharacter->ID < CurrentID)
			{
				SheepToFollow = EachCharacter;
				CurrentID = EachCharacter->ID;
			}
		}
		// If the sensed actor is a dog, move towards the pen
		else if (EachActor->GetClass()->IsChildOf(ADogPawn::StaticClass()))
		{

			srand(time(NULL));

			int GoToPositionX = (rand() % 155) - 77;
			int GoToPositionY = (rand() % 161) - 417;

			MoveToLocation((FVector(GoToPositionX, GoToPositionY, 36.0f)), -1, false);
		}

	}

	if (SheepToFollow)
	{
		ASheepAIController* Con = Cast<ASheepAIController>(SheepToFollow->GetController());

		if (Con)
		{
			MoveToLocation((Con->TargetLocation), -1, false);
		}
	}


}

void ASheepAIController::BeginPlay()
{

	Super::BeginPlay();

}

void ASheepAIController::MoveSheep()
{
	FVector ClosestWall = FindClosestWall();

	MoveToLocation(ClosestWall, -1, false);

	TargetLocation = ClosestWall;

}

FVector ASheepAIController::FindClosestWall()
{
	AEdgeWall* ClosestWall = nullptr;
	float CurrentDist = 0.0f;
	float ShortestDist = 100000.0f;
	FVector CurrentPos = GetPawn()->GetActorLocation();

	for (AEdgeWall* EachEdgeWall : EdgeWalls)
	{
		FVector WallPos = EachEdgeWall->GetActorLocation();
		CurrentDist = FVector::Dist(CurrentPos, WallPos);

		if (CurrentDist < ShortestDist)
		{
			ClosestWall = EachEdgeWall;
			ShortestDist = CurrentDist;
		}

	}

	if (ClosestWall != nullptr)
	{

		FVector ClosestLocation = ClosestWall->GetActorLocation();

		// Moves the sheep towards a random location along the nearest edge wall
		if ((ClosestWall->GetName() == "TopWall") || (ClosestWall->GetName() == "BottomWall"))
		{
			float Offset = GetRandomNumber(-585.0f, 585.0f);
			ClosestLocation.Y = ClosestLocation.Y + Offset;
		}
		else
		{
			float Offset = GetRandomNumber(-380.0f, 365.0f);
			ClosestLocation.X = ClosestLocation.X + Offset;
		}

		return ClosestLocation;

	}
	else
	{
		return FVector(0.0f, 0.0f, 0.0f);
	}
}

void ASheepAIController::FindAllEdgeWalls()
{

	for (AEdgeWall* EachWall : TActorRange<AEdgeWall>(GetWorld()))
	{
		EdgeWalls.Add(EachWall);
	}

}

float ASheepAIController::GetRandomNumber(float min, float max)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	static std::uniform_real_distribution<float> dis(min, max);

	return dis(rd);
}

