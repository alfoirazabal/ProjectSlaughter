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

	this->trainClass = nullptr;
	this->trainTrafficLights = nullptr;

	this->demoConstantsHelper = new SlaughterFirendsDemoConstants();
}

void ATrainAISpawner::SetRedLight() const
{
	if (this->trainTrafficLights != nullptr) {
		this->trainTrafficLights->bGreenLightOn = false;
		this->trainTrafficLights->bYellowLightOn = false;
		this->trainTrafficLights->bRedLightOn = true;
	}
}

void ATrainAISpawner::SetYellowLight() const
{
	if (this->trainTrafficLights != nullptr) {
		this->trainTrafficLights->bGreenLightOn = false;
		this->trainTrafficLights->bYellowLightOn = true;
		this->trainTrafficLights->bRedLightOn = false;
	}
}

void ATrainAISpawner::SetGreenLight() const
{
	if (this->trainTrafficLights != nullptr) {
		this->trainTrafficLights->bGreenLightOn = true;
		this->trainTrafficLights->bYellowLightOn = false;
		this->trainTrafficLights->bRedLightOn = false;
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
	if (this->trainClass != nullptr)
	{
		ATrainAI* Train = this->GetWorld()->SpawnActor<ATrainAI>(this->trainClass, this->GetActorLocation(), this->GetActorRotation());
		Train->speed = this->travelSpeed;
		Train->direction = this->direction;
		Train->maxTravelDistance = this->maxDistance;
	}
}

// Called every frame
void ATrainAISpawner::Tick(const float DeltaTime)
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
