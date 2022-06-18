// Fill out your copyright notice in the Description page of Project Settings.


#include "Props/ElevatorLights/ElevatorLightAI.h"

// Sets default values
AElevatorLightAI::AElevatorLightAI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	this->bRedLightOn = false;
	this->bYellowLightOn = false;
	this->bGreenLightOn = false;

}

// Called when the game starts or when spawned
void AElevatorLightAI::BeginPlay()
{
	Super::BeginPlay();
	TArray<UPointLightComponent*> PointLightComponents;
	this->GetComponents(PointLightComponents);
	for (int i = 0 ; i < PointLightComponents.Num() ; i++)
	{
		if (PointLightComponents[i]->GetName().Equals("RedLight"))
		{
			this->RedLight = PointLightComponents[i];
		}
		else if (PointLightComponents[i]->GetName().Equals("YellowLight"))
		{
			this->YellowLight = PointLightComponents[i];
		}
		else if (PointLightComponents[i]->GetName().Equals("GreenLight"))
		{
			this->GreenLight = PointLightComponents[i];
		}
	}
}

// Called every frame
void AElevatorLightAI::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->RedLight->SetVisibility(this->bRedLightOn);
	this->YellowLight->SetVisibility(this->bYellowLightOn);
	this->GreenLight->SetVisibility(this->bGreenLightOn);
}

