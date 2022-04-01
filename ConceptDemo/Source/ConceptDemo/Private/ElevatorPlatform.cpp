// Fill out your copyright notice in the Description page of Project Settings.


#include "ElevatorPlatform.h"

AElevatorPlatform::PLATFORM_STATUS CurrentPlatformStatus;

// Sets default values
AElevatorPlatform::AElevatorPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->isActivated = false;
	this->floorLevel = 0;
	this->ceilingLevel = 0;
	this->stillTime = 5;
	this->speed = 5;
	CurrentPlatformStatus = PLATFORM_STATUS::MOVING_UP;

	this->currentStillTime = this->stillTime;
}

AElevatorPlatform::PLATFORM_STATUS AElevatorPlatform::GetPlatformStatus() 
{
	return CurrentPlatformStatus;
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
		if (this->currentStillTime == 0) {
			FVector currentLocation = this->GetActorLocation();
			switch (CurrentPlatformStatus) {
				case PLATFORM_STATUS::MOVING_UP:
					currentLocation.Z += this->speed * DeltaTime;
					break;
				case PLATFORM_STATUS::MOVING_DOWN:
					currentLocation.Z -= this->speed * DeltaTime;
					break;
			}
			if (currentLocation.Z >= this->ceilingLevel) {
				CurrentPlatformStatus = PLATFORM_STATUS::STATIONED_UP;
				this->currentStillTime = this->stillTime;
			}
			else if (currentLocation.Z <= this->floorLevel) {
				CurrentPlatformStatus = PLATFORM_STATUS::STATIONED_DOWN;
				this->currentStillTime = this->stillTime;
			}
			SetActorLocation(currentLocation);
		}
		else {
			this->currentStillTime--;
			if (this->currentStillTime == 0) {
				if (CurrentPlatformStatus == PLATFORM_STATUS::STATIONED_DOWN) {
					CurrentPlatformStatus = PLATFORM_STATUS::MOVING_UP;
;				}
				else if (CurrentPlatformStatus == PLATFORM_STATUS::STATIONED_UP) {
					CurrentPlatformStatus = PLATFORM_STATUS::MOVING_DOWN;
				}
			}
		}
		
	}
}

