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
	this->maxSpawnTime = 1000;

	this->trainDistanceOnYellowLight = 300;
	this->redLightOnTime = 3000 / (this->travelSpeed * 2.3);
	this->redLightTimeLeft = 0;

	this->currentSpawnTime = 0;

	this->trainClass = NULL;
	this->trainTrafficLights = NULL;

	this->demoConstantsHelper = new SlaughterFirendsDemoConstants();
}

void ATrainAISpawner::SetRedLight()
{
	if (this->trainTrafficLights != NULL) {
		this->trainTrafficLights->greenLightOn = false;
		this->trainTrafficLights->yellowLightOn = false;
		this->trainTrafficLights->redLightOn = true;
	}
}

void ATrainAISpawner::SetYellowLight()
{
	if (this->trainTrafficLights != NULL) {
		this->trainTrafficLights->greenLightOn = false;
		this->trainTrafficLights->yellowLightOn = true;
		this->trainTrafficLights->redLightOn = false;
	}
}

void ATrainAISpawner::SetGreenLight() 
{
	if (this->trainTrafficLights != NULL) {
		this->trainTrafficLights->greenLightOn = true;
		this->trainTrafficLights->yellowLightOn = false;
		this->trainTrafficLights->redLightOn = false;
	}
}

// Called when the game starts or when spawned
void ATrainAISpawner::BeginPlay()
{
	Super::BeginPlay();
	this->SetGreenLight();
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
		this->SpawnVehicle();
		this->redLightTimeLeft = this->redLightOnTime;
		this->currentSpawnTime = 0;
	}
	else {
		this->currentSpawnTime++;
		if (this->redLightTimeLeft > 0) {
			this->SetRedLight();
			this->redLightTimeLeft--;
		}
		else {
			if (this->randSpawnTime - this->currentSpawnTime < this->trainDistanceOnYellowLight) {
				this->SetYellowLight();
			}
			else {
				this->SetGreenLight();
			}
		}
	}
}
