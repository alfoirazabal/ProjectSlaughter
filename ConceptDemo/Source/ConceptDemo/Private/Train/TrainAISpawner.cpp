// Fill out your copyright notice in the Description page of Project Settings.


#include "Train/TrainAISpawner.h"

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

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

	if (this->TrainArrivalSound)
	{
		this->TrainArrivalSoundComponent = UGameplayStatics::SpawnSound2D(this->GetWorld(), this->TrainArrivalSound);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(189522350, 2, FColor::Yellow, "Train arrival sound not set");
	}
	if (!this->TrainPassingSound) 
	{
		GEngine->AddOnScreenDebugMessage(189522351, 2, FColor::Yellow, "Train passing sound not set");
	}
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
			if (this->trainTrafficLights && !this->trainTrafficLights->bRedLightOn)
			{
				this->SetRedLight();
				if (this->TrainOnStationSound) UGameplayStatics::PlaySound2D(this->GetWorld(), this->TrainOnStationSound);
			}
			this->redLightTimeLeft--;
		}
		else {
			if (this->randSpawnTime - this->currentSpawnTime < this->trainDistanceOnYellowLight) {
				if (this->trainTrafficLights && !this->trainTrafficLights->bYellowLightOn)
				{
					this->SetYellowLight();
					if (this->TrainPassingSound) UGameplayStatics::PlaySound2D(this->GetWorld(), this->TrainPassingSound);
				}
			}
			else {
				this->SetGreenLight();
				if (this->TrainArrivalSoundComponent) this->TrainArrivalSoundComponent->Stop();
			}
		}
	}
	if (this->trainTrafficLights->bRedLightOn || this->trainTrafficLights->bYellowLightOn)
	{
		if (this->TrainArrivalSound)
		{
			if (!this->TrainArrivalSoundComponent)
			{
				this->TrainArrivalSoundComponent = UGameplayStatics::SpawnSound2D(this->GetWorld(), this->TrainArrivalSound);
			}
			if (!this->TrainArrivalSoundComponent->IsPlaying()) this->TrainArrivalSoundComponent->Play();
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(236723334, 2, FColor::Yellow, "Train arrival sound not set for TrainAISpawner");
		}
	}
}
