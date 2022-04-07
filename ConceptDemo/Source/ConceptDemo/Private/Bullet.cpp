// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->InitialPosition = this->GetActorLocation();
	this->TravelSpeed = 3;
	this->TotalDistanceTraveled = 0;
	this->MaxTravelDistance = 5000;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABullet::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector CurrentPosition = this->GetActorLocation();
	if (this->FacingDirection == EFacing_Direction::Right) {
		CurrentPosition.Y += this->TravelSpeed;
	}
	else if (this->FacingDirection == EFacing_Direction::Left) {
		CurrentPosition.Y -= this->TravelSpeed;
	}
	this->SetActorLocation(CurrentPosition);
	this->TotalDistanceTraveled += this->TravelSpeed;
	if (this->TotalDistanceTraveled >= this->MaxTravelDistance) {
		this->Destroy();
	}
}

