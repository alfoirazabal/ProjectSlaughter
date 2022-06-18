// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/ElevatorLights/ElevatorLightSetter.h"

// Sets default values
AElevatorLightSetter::AElevatorLightSetter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->ElevatorLight = nullptr;
	this->ElevatorPlatform = nullptr;
}

// Called when the game starts or when spawned
void AElevatorLightSetter::BeginPlay()
{
	Super::BeginPlay();
	if (this->ElevatorLight == nullptr) {
		GEngine->AddOnScreenDebugMessage(43121963, 5, FColor::Red, "Need to setup elevator light for ElevatorLightSetter!");
	}
	if (this->ElevatorPlatform == nullptr) {
		GEngine->AddOnScreenDebugMessage(43121964, 5, FColor::Red, "Need to setup elevator platform for ElevatorLightSetter!");
	}
}

// Called every frame
void AElevatorLightSetter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this->ElevatorPlatform->PlatformStatus == EPlatform_Status::Moving) {
		this->ElevatorLight->MiddleGreenLight->SetVisibility(false);
		this->ElevatorLight->SpikesRedLight->SetVisibility(false);
		this->ElevatorLight->SubwayRedLight->SetVisibility(false);
		switch (this->ElevatorPlatform->MovingDirection) {
			case EPlatform_Moving_Direction::Moving_Down:
				this->ElevatorLight->YellowDownLight->SetVisibility(true);
				this->ElevatorLight->YellowUpLight->SetVisibility(false);
				break;
			case EPlatform_Moving_Direction::Moving_Up:
				this->ElevatorLight->YellowDownLight->SetVisibility(false);
				this->ElevatorLight->YellowUpLight->SetVisibility(true);
				break;
			default:
				break;
		}
		switch (this->ElevatorPlatform->GetTargetLocation()) {
			case EPlatform_Status::On_Ceiling:
				this->ElevatorLight->SpikesRedLight->SetVisibility(true);
				break;
			case EPlatform_Status::On_Middle:
				this->ElevatorLight->MiddleGreenLight->SetVisibility(true);
				break;
			case EPlatform_Status::On_Floor:
				this->ElevatorLight->SubwayRedLight->SetVisibility(true);
				break;
			default:
				break;
		}
	}
	else {
		switch (this->ElevatorPlatform->PlatformStatus) {
			case EPlatform_Status::On_Ceiling:
				this->ElevatorLight->SpikesRedLight->SetVisibility(true);
				this->ElevatorLight->YellowDownLight->SetVisibility(true);
				this->ElevatorLight->YellowUpLight->SetVisibility(false);
				break;
			case EPlatform_Status::On_Middle:
				this->ElevatorLight->MiddleGreenLight->SetVisibility(true);
				break;
			case EPlatform_Status::On_Floor:
				this->ElevatorLight->SubwayRedLight->SetVisibility(true);
				this->ElevatorLight->YellowUpLight->SetVisibility(true);
				this->ElevatorLight->YellowDownLight->SetVisibility(false);
				break;
			default:
				break;
		}
	}
}

