// Fill out your copyright notice in the Description page of Project Settings.


#include "DogPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "SHCGameModeBase.h"
#include "SheepHerdChallenge/Sheep/SheepBaseCharacter.h"
#include "EngineUtils.h"

ADogPlayerController::ADogPlayerController()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	UAIPerceptionSystem::RegisterPerceptionStimuliSource(this, SightConfig->GetSenseImplementation(), GetPawn());

	OverallScore = 0.0f;
	CurrentScore = 0.0f;

}

void ADogPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ADogPlayerController::SetUpdatedCurrentScore(float Score)
{

	CurrentScore = CurrentScore + Score;

}

float ADogPlayerController::GetCurrentScore() const
{
	return CurrentScore;
}

void ADogPlayerController::SetSheepCapturedInLevel(int NumSheep)
{
	SheepCapturedInLevel = SheepCapturedInLevel + NumSheep;
}

float ADogPlayerController::GetSheepCapturedInLevel() const
{
	return SheepCapturedInLevel;
}

void ADogPlayerController::EndLevel()
{
	OverallScore = OverallScore + CurrentScore;
	OverallSheep = OverallSheep + SheepCapturedInLevel;

	if (EndLevelWidgetClass != nullptr)
	{
		EndLevelWidget = CreateWidget<UUserWidget>(GetWorld(), EndLevelWidgetClass);
		EndLevelWidget->AddToViewport();
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = true;
		GetWorld()->GetFirstPlayerController()->bEnableClickEvents = true;
	}
}

int ADogPlayerController::GetCurrentLevel() const
{
	return CurrentLevel;
}

void ADogPlayerController::NextLevel()
{

	ASHCGameModeBase* GM = Cast<ASHCGameModeBase>(GetWorld()->GetAuthGameMode());

	if (GM)
	{
		// Dsetroy all sheep remaining in level
		for (ASheepBaseCharacter* EachSheep : TActorRange<ASheepBaseCharacter>(GetWorld()))
		{
			EachSheep->DestroySelf();
		}

		// Increment level
		CurrentLevel++;

		// Sets overall score and restarts level
		GM->RecordScore(CurrentScore, SheepCapturedInLevel);
		GM->SetUpLevel(CurrentLevel);
	}

	// Removes UI widget from screen
	if (EndLevelWidgetClass != nullptr)
	{
		EndLevelWidget->RemoveFromViewport();
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		GetWorld()->GetFirstPlayerController()->bShowMouseCursor = false;
		GetWorld()->GetFirstPlayerController()->bEnableClickEvents = false;
	}
}

float ADogPlayerController::GetOverallScore()
{
	return OverallScore;
}

float ADogPlayerController::GetOverallSheep()
{
	return OverallSheep;
}


