// Fill out your copyright notice in the Description page of Project Settings.


#include "ElevatorPlatform.h"

// Sets default values
AElevatorPlatform::AElevatorPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->bIsActivated = true;
	this->FloorLevel = 0;
	this->MiddleLevel = 0;
	this->CeilingLevel = 0;
	this->StillTime = 5;
	this->Speed = 5;

	this->MovingDirection = EPlatform_Moving_Direction::Moving_Up;

	this->CurrentStillTime = this->StillTime;

	this->bInTheMiddle = false;
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
	if (this->bIsActivated) {
		if (this->CurrentStillTime == 0) {
			FVector currentLocation = this->GetActorLocation();
			float zLocation = currentLocation.Z;
			if (zLocation >= this->CeilingLevel && this->MovingDirection != EPlatform_Moving_Direction::Moving_Down) {
				this->MovingDirection = EPlatform_Moving_Direction::Moving_Down;
				this->CurrentStillTime = this->StillTime;
				this->bInTheMiddle = false;
				this->PlatformStatus = EPlatform_Status::On_Ceiling;
				this->LastStaticStatus = this->PlatformStatus;
			}
			else if (
					zLocation <= this->MiddleLevel + this->Speed && 
					zLocation >= this->MiddleLevel - this->Speed &&
					!this->bInTheMiddle
			) {
				this->bInTheMiddle = true;
				this->CurrentStillTime = this->StillTime;
				this->PlatformStatus = EPlatform_Status::On_Middle;
				this->LastStaticStatus = this->PlatformStatus;
			}
			else if (zLocation <= this->FloorLevel && this->MovingDirection != EPlatform_Moving_Direction::Moving_Up) {
				this->MovingDirection = EPlatform_Moving_Direction::Moving_Up;
				this->CurrentStillTime = this->StillTime;
				this->bInTheMiddle = false;
				this->PlatformStatus = EPlatform_Status::On_Floor;
				this->LastStaticStatus = this->PlatformStatus;
			}
			else {
				this->PlatformStatus = EPlatform_Status::Moving;
				switch (this->MovingDirection) {
					case EPlatform_Moving_Direction::Moving_Down:
						zLocation -= this->Speed;
						break;
					case EPlatform_Moving_Direction::Moving_Up:
						zLocation += this->Speed;
						break;
					default:
						break;
				}
				currentLocation.Z = zLocation;
				this->SetActorLocation(currentLocation);
			}
		}
		else {
			this->CurrentStillTime--;
		}
	}
}

EPlatform_Status AElevatorPlatform::GetTargetLocation() const
{
	switch (this->LastStaticStatus) {
		case EPlatform_Status::On_Ceiling:
			return EPlatform_Status::On_Middle;
		case EPlatform_Status::On_Middle:
			switch (this->MovingDirection) {
				case EPlatform_Moving_Direction::Moving_Down:
					return EPlatform_Status::On_Floor;
				case EPlatform_Moving_Direction::Moving_Up:
					return EPlatform_Status::On_Ceiling;
				default:
					return EPlatform_Status::Moving;
			}
		case EPlatform_Status::On_Floor:
			return EPlatform_Status::On_Middle;
		default:
			return EPlatform_Status::Moving;
	}
}
