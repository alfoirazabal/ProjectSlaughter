// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->initialPosition = this->GetActorLocation();
	this->TravelSpeed = 3;
	this->totalDistanceTraveled = 0;
	this->MaxTravelDistance = 5000;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector currentPosition = this->GetActorLocation();
	if (this->FacingDirection == FACING_DIRECTION::RIGHT) {
		currentPosition.Y += this->TravelSpeed;
	}
	else if (this->FacingDirection == FACING_DIRECTION::LEFT) {
		currentPosition.Y -= this->TravelSpeed;
	}
	this->SetActorLocation(currentPosition);
	this->totalDistanceTraveled += this->TravelSpeed;
	if (this->totalDistanceTraveled >= this->MaxTravelDistance) {
		this->Destroy();
	}
}

