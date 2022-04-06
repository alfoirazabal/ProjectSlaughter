// Fill out your copyright notice in the Description page of Project Settings.


#include "ElevatorPlatform.h"

// Sets default values
AElevatorPlatform::AElevatorPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->isActivated = true;
	this->floorLevel = 0;
	this->middleLevel = 0;
	this->ceilingLevel = 0;
	this->stillTime = 5;
	this->speed = 5;

	this->MovingDirection = PLATFORM_MOVING_DIRECTION::MOVING_UP;

	this->currentStillTime = this->stillTime;

	this->inTheMiddle = false;
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
			float zLocation = currentLocation.Z;
			if (zLocation >= this->ceilingLevel && this->MovingDirection != PLATFORM_MOVING_DIRECTION::MOVING_DOWN) {
				this->MovingDirection = PLATFORM_MOVING_DIRECTION::MOVING_DOWN;
				this->currentStillTime = this->stillTime;
				this->inTheMiddle = false;
				this->PlatformStatus = PLATFORM_STATUS::ON_CEILING;
				this->lastStaticStatus = this->PlatformStatus;
			}
			else if (
					zLocation <= this->middleLevel + this->speed && 
					zLocation >= this->middleLevel - this->speed &&
					!this->inTheMiddle
			) {
				this->inTheMiddle = true;
				this->currentStillTime = this->stillTime;
				this->PlatformStatus = PLATFORM_STATUS::ON_MIDDLE;
				this->lastStaticStatus = this->PlatformStatus;
			}
			else if (zLocation <= this->floorLevel && this->MovingDirection != PLATFORM_MOVING_DIRECTION::MOVING_UP) {
				this->MovingDirection = PLATFORM_MOVING_DIRECTION::MOVING_UP;
				this->currentStillTime = this->stillTime;
				this->inTheMiddle = false;
				this->PlatformStatus = PLATFORM_STATUS::ON_FLOOR;
				this->lastStaticStatus = this->PlatformStatus;
			}
			else {
				this->PlatformStatus = PLATFORM_STATUS::MOVING;
				switch (this->MovingDirection) {
					case PLATFORM_MOVING_DIRECTION::MOVING_DOWN:
						zLocation -= this->speed;
						break;
					case PLATFORM_MOVING_DIRECTION::MOVING_UP:
						zLocation += this->speed;
						break;
				}
				currentLocation.Z = zLocation;
				this->SetActorLocation(currentLocation);
			}
		}
		else {
			this->currentStillTime--;
		}
	}
}

PLATFORM_STATUS AElevatorPlatform::GetTargetLocation() {
	switch (this->lastStaticStatus) {
		case PLATFORM_STATUS::ON_CEILING:
			return PLATFORM_STATUS::ON_MIDDLE;
		case PLATFORM_STATUS::ON_MIDDLE:
			switch (this->MovingDirection) {
				case PLATFORM_MOVING_DIRECTION::MOVING_DOWN:
					return PLATFORM_STATUS::ON_FLOOR;
				case PLATFORM_MOVING_DIRECTION::MOVING_UP:
					return PLATFORM_STATUS::ON_CEILING;
				default:
					return PLATFORM_STATUS::MOVING;
			}
		case PLATFORM_STATUS::ON_FLOOR:
			return PLATFORM_STATUS::ON_MIDDLE;
		default:
			return PLATFORM_STATUS::MOVING;
	}
}