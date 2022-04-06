// Fill out your copyright notice in the Description page of Project Settings.


#include "ElevatorLightSetter.h"

// Sets default values
AElevatorLightSetter::AElevatorLightSetter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->elevatorLight = NULL;
	this->elevatorPlatform = NULL;
}

// Called when the game starts or when spawned
void AElevatorLightSetter::BeginPlay()
{
	Super::BeginPlay();
	if (this->elevatorLight == NULL) {
		GEngine->AddOnScreenDebugMessage(43121963, 5, FColor::Red, "Need to setup elevator light for ElevatorLightSetter!");
	}
	if (this->elevatorPlatform == NULL) {
		GEngine->AddOnScreenDebugMessage(43121964, 5, FColor::Red, "Need to setup elevator platform for ElevatorLightSetter!");
	}
}

// Called every frame
void AElevatorLightSetter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this->elevatorPlatform->PlatformStatus == PLATFORM_STATUS::MOVING) {
		this->elevatorLight->MiddleGreenLight->SetVisibility(false);
		this->elevatorLight->SpikesRedLight->SetVisibility(false);
		this->elevatorLight->SubwayRedLight->SetVisibility(false);
		switch (this->elevatorPlatform->MovingDirection) {
			case PLATFORM_MOVING_DIRECTION::MOVING_DOWN:
				this->elevatorLight->YellowDownLight->SetVisibility(true);
				this->elevatorLight->YellowUpLight->SetVisibility(false);
				break;
			case PLATFORM_MOVING_DIRECTION::MOVING_UP:
				this->elevatorLight->YellowDownLight->SetVisibility(false);
				this->elevatorLight->YellowUpLight->SetVisibility(true);
				break;
		}
		switch (this->elevatorPlatform->GetTargetLocation()) {
			case PLATFORM_STATUS::ON_CEILING:
				this->elevatorLight->SpikesRedLight->SetVisibility(true);
				break;
			case PLATFORM_STATUS::ON_MIDDLE:
				this->elevatorLight->MiddleGreenLight->SetVisibility(true);
				break;
			case PLATFORM_STATUS::ON_FLOOR:
				this->elevatorLight->SubwayRedLight->SetVisibility(true);
				break;
		}
	}
	else {
		switch (this->elevatorPlatform->PlatformStatus) {
			case PLATFORM_STATUS::ON_CEILING:
				this->elevatorLight->SpikesRedLight->SetVisibility(true);
				this->elevatorLight->YellowDownLight->SetVisibility(true);
				this->elevatorLight->YellowUpLight->SetVisibility(false);
				break;
			case PLATFORM_STATUS::ON_MIDDLE:
				this->elevatorLight->MiddleGreenLight->SetVisibility(true);
				break;
			case PLATFORM_STATUS::ON_FLOOR:
				this->elevatorLight->SubwayRedLight->SetVisibility(true);
				this->elevatorLight->YellowUpLight->SetVisibility(true);
				this->elevatorLight->YellowDownLight->SetVisibility(false);
				break;
		}
	}
}

