// Fill out your copyright notice in the Description page of Project Settings.


#include "SheepBaseCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "SheepAIController.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SheepHerdChallenge/SHCGameModeBase.h"
#include "SheepHerdChallenge/DogPlayerController.h"
#include "SheepHerdChallenge/Scenery/EdgeWall.h"

int ASheepBaseCharacter::ID = 0;

// Sets default values
ASheepBaseCharacter::ASheepBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sheep = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SheepSM"));
	Sheep->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SheepAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cylinder.Shape_Cylinder"));

	if (SheepAsset.Succeeded())
	{
		Sheep->SetStaticMesh(SheepAsset.Object);
		Sheep->SetRelativeLocation(FVector(0.0f, 0.0f, -50.0f));
	}

	RootComponent->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.06f));

	AIControllerClass = ASheepAIController::StaticClass();

	ID++;

}

// Called when the game starts or when spawned
void ASheepBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	this->SpawnDefaultController();

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &ASheepBaseCharacter::OnHit);

	ADogPlayerController* Dog = Cast<ADogPlayerController>(GetWorld()->GetFirstPlayerController());

	if (Dog)
	{
		SetMaxSpeed(Dog->GetCurrentLevel());
	}

	GetCharacterMovement()->MaxWalkSpeed = MaxSpeed;

}

// Called every frame
void ASheepBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASheepBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ASheepBaseCharacter::DestroySelf()
{

	auto controllerRef = Controller;
	Controller->UnPossess();
	controllerRef->Destroy();

	this->Destroy();

}

void ASheepBaseCharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{

	if (OtherActor && (OtherActor != this) && OtherActor->GetClass()->IsChildOf(AEdgeWall::StaticClass()))
	{

		DestroySelf();

	}

}

void ASheepBaseCharacter::SetMaxSpeed(int Level)
{

	MaxSpeed = MaxSpeed + (Level * 2);


	if (MaxSpeed > 200.0f)
	{
		MaxSpeed = 200.0f;
	}

}
