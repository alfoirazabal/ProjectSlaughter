// Fill out your copyright notice in the Description page of Project Settings.


#include "Train/TrainAI.h"

// Sets default values
ATrainAI::ATrainAI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->speed = 1;
	this->direction = FVector::ZeroVector;
	this->maxTravelDistance = 500;
}

// Called when the game starts or when spawned
void ATrainAI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrainAI::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector CurrentPosition = this->GetActorLocation();
	const float NewXRelativePosition = this->direction.X * this->speed;
	const float NewYRelativePosition = this->direction.Y * this->speed;
	CurrentPosition.X += NewXRelativePosition;
	CurrentPosition.Y += NewYRelativePosition;
	this->SetActorLocation(CurrentPosition);
	this->distanceTraveled += hypot(NewXRelativePosition, NewYRelativePosition);
	if (this->distanceTraveled >= this->maxTravelDistance) {
		this->Destroy();
	}
}

