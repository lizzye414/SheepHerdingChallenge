// Fill out your copyright notice in the Description page of Project Settings.


#include "EdgeTriggerBox.h"
#include "SheepHerdChallenge/Sheep/SheepBaseCharacter.h"

AEdgeTriggerBox::AEdgeTriggerBox()
{
}

void AEdgeTriggerBox::BeginPlay()
{
    Super::BeginPlay();

    //Register Events
    OnActorBeginOverlap.AddDynamic(this, &AEdgeTriggerBox::OnOverlap);

}


void AEdgeTriggerBox::OnOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
    // If a sheep enters edge trigger box, the sheep is destroyed
    if (OtherActor && (OtherActor != this) && (OtherActor->GetClass()->IsChildOf(ASheepBaseCharacter::StaticClass())))
    {

        ASheepBaseCharacter* CurrentSheep = Cast<ASheepBaseCharacter>(OtherActor);
        CurrentSheep->DestroySelf();

    }

}