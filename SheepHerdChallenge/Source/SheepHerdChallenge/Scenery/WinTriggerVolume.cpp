// Fill out your copyright notice in the Description page of Project Settings.


#include "WinTriggerVolume.h"
#include "SheepHerdChallenge/Sheep/SheepBaseCharacter.h"
#include "SheepHerdChallenge/DogPlayerController.h"

void AWinTriggerVolume::BeginPlay()
{
    Super::BeginPlay();

    //Register Events
    OnActorBeginOverlap.AddDynamic(this, &AWinTriggerVolume::OnOverlapBegin);
    OnActorEndOverlap.AddDynamic(this, &AWinTriggerVolume::OnOverlapEnd);

}

void AWinTriggerVolume::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
    // Increment sheep counter when sheep enters trigger volume
    if (OtherActor && (OtherActor != this) && OtherActor->GetClass()->IsChildOf(ASheepBaseCharacter::StaticClass()))
    {
        ASheepBaseCharacter* Sheep = Cast<ASheepBaseCharacter>(OtherActor);
        ADogPlayerController* PlayerCon = Cast<ADogPlayerController>(GetWorld()->GetFirstPlayerController());

        PlayerCon->SetUpdatedCurrentScore(Sheep->WinPoints);
        PlayerCon->SetSheepCapturedInLevel(1);

    }

}

void AWinTriggerVolume::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
    // Decrement sheep counter when sheep leaves trigger volume
    if (OtherActor && (OtherActor != this) && OtherActor->GetClass()->IsChildOf(ASheepBaseCharacter::StaticClass()))
    {
        ASheepBaseCharacter* Sheep = Cast<ASheepBaseCharacter>(OtherActor);
        ADogPlayerController* PlayerCon = Cast<ADogPlayerController>(GetWorld()->GetFirstPlayerController());

        PlayerCon->SetUpdatedCurrentScore(-Sheep->WinPoints);
        PlayerCon->SetSheepCapturedInLevel(-1);

    }

}
