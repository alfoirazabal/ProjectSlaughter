// Fill out your copyright notice in the Description page of Project Settings.


#include "ElevatorPlatform.h"

enum PLATFORM_DIRECTION {
	GOING_UP,
	GOING_DOWN
};

PLATFORM_DIRECTION CurrentPlatformDirection;

// Sets default values
AElevatorPlatform::AElevatorPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->isActivated = false;
	this->floorLevel = 0;
	this->ceilingLevel = 0;
	this->speed = 5;
	CurrentPlatformDirection = PLATFORM_DIRECTION::GOING_UP;
}

// Called when the game starts or when spawned
void AElevatorPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AElevatorPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this->isActivated) {
		FVector currentLocation = this->GetActorLocation();
		switch (CurrentPlatformDirection) {
			case PLATFORM_DIRECTION::GOING_UP:
				currentLocation.Z += this->speed * DeltaTime;
				break;
			case PLATFORM_DIRECTION::GOING_DOWN:
				currentLocation.Z -= this->speed * DeltaTime;
				break;
		}
		if (currentLocation.Z >= this->ceilingLevel) {
			CurrentPlatformDirection = PLATFORM_DIRECTION::GOING_DOWN;
		}
		else if (currentLocation.Z <= this->floorLevel) {
			CurrentPlatformDirection = PLATFORM_DIRECTION::GOING_UP;
		}
		SetActorLocation(currentLocation);
	}
}

