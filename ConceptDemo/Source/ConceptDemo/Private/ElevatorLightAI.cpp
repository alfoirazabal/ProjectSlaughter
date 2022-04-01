// Fill out your copyright notice in the Description page of Project Settings.


#include "ElevatorLightAI.h"

// Sets default values
AElevatorLightAI::AElevatorLightAI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	this->redLightOn = false;
	this->yellowLightOn = false;
	this->greenLightOn = false;

	this->elevatorPlatform = NULL;

}

// Called when the game starts or when spawned
void AElevatorLightAI::BeginPlay()
{
	Super::BeginPlay();

	TArray<UActorComponent*> Components = this->GetComponentsByClass(UPointLightComponent::StaticClass());
	GEngine->AddOnScreenDebugMessage(345235, 2, FColor::Yellow, FString::FromInt(Components.Num()));
	for (int32 i = 0; i < Components.Num(); i++)
	{
		if (Components[i]->GetName().Equals("RedLight")) {
			this->redLight = Cast<UPointLightComponent>(Components[i]);
		}
		else if (Components[i]->GetName().Equals("YellowLight")) {
			this->yellowLight = Cast<UPointLightComponent>(Components[i]);
		}
		else if (Components[i]->GetName().Equals("GreenLight")) {
			this->greenLight = Cast<UPointLightComponent>(Components[i]);
		}
	}
	
}

// Called every frame
void AElevatorLightAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->redLight->SetVisibility(this->redLightOn);
	this->yellowLight->SetVisibility(this->yellowLightOn);
	this->greenLight->SetVisibility(this->greenLightOn);

	if (this->elevatorPlatform != NULL) {
		switch (this->elevatorPlatform->GetPlatformStatus()) {
			case AElevatorPlatform::PLATFORM_STATUS::STATIONED_DOWN:
				this->redLight->SetVisibility(false);
				this->yellowLight->SetVisibility(false);
				this->greenLight->SetVisibility(true);
				break;
			case AElevatorPlatform::PLATFORM_STATUS::MOVING_DOWN:
				this->redLight->SetVisibility(false);
				this->yellowLight->SetVisibility(true);
				this->greenLight->SetVisibility(false);
				break;
			case AElevatorPlatform::PLATFORM_STATUS::MOVING_UP:
				this->redLight->SetVisibility(true);
				this->yellowLight->SetVisibility(true);
				this->greenLight->SetVisibility(false);
				break;
			case AElevatorPlatform::PLATFORM_STATUS::STATIONED_UP:
				this->redLight->SetVisibility(true);
				this->yellowLight->SetVisibility(false);
				this->greenLight->SetVisibility(false);
				break;
		}
	}
}

