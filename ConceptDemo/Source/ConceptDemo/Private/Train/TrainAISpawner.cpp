// Fill out your copyright notice in the Description page of Project Settings.


#include "Train/TrainAISpawner.h"

// Sets default values
ATrainAISpawner::ATrainAISpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->travelSpeed = 4;
	this->maxDistance = 5000;
	this->minSpawnTime = 400;
	this->maxSpawnTime = 700;

	this->currentSpawnTime = 0;

	this->trainClass = NULL;

	this->demoConstantsHelper = new SlaughterFirendsDemoConstants();
}

// Called when the game starts or when spawned
void ATrainAISpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATrainAISpawner::SpawnVehicle()
{
	if (this->trainClass != NULL)
	{
		ATrainAI* train = this->GetWorld()->SpawnActor<ATrainAI>(this->trainClass, this->GetActorLocation(), this->GetActorRotation());
		train->speed = this->travelSpeed;
		train->direction = this->direction;
		train->maxTravelDistance = this->maxDistance;
	}
}

// Called every frame
void ATrainAISpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this->currentSpawnTime == 0)
	{
		this->randSpawnTime = this->demoConstantsHelper->GenerateBoundedFloat(this->minSpawnTime, this->maxSpawnTime);
	}
	if (this->currentSpawnTime >= this->randSpawnTime) {
		GEngine->AddOnScreenDebugMessage(456346, 2, FColor::Green, "Will spawn train");
		this->SpawnVehicle();
		this->currentSpawnTime = 0;
	}
	else {
		this->currentSpawnTime++;
	}
}
