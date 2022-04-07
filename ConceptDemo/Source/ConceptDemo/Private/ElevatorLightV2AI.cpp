// Fill out your copyright notice in the Description page of Project Settings.


#include "ElevatorLightV2AI.h"

// Sets default values
AElevatorLightV2AI::AElevatorLightV2AI()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AElevatorLightV2AI::BeginPlay()
{
	Super::BeginPlay();

	TArray<UPointLightComponent*> Components;
	this->GetComponents(Components);
	for (int32 i = 0; i < Components.Num(); i++)
	{
		if (Components[i]->GetName().Equals("SpikesRedLight")) {
			this->SpikesRedLight = Cast<UPointLightComponent>(Components[i]);
		}
		else if (Components[i]->GetName().Equals("YellowUpLight")) {
			this->YellowUpLight = Cast<UPointLightComponent>(Components[i]);
		}
		else if (Components[i]->GetName().Equals("YellowDownLight")) {
			this->YellowDownLight = Cast<UPointLightComponent>(Components[i]);
		}
		else if (Components[i]->GetName().Equals("MiddleGreenLight")) {
			this->MiddleGreenLight = Cast<UPointLightComponent>(Components[i]);
		}
		else if (Components[i]->GetName().Equals("SubwayRedLight")) {
			this->SubwayRedLight = Cast<UPointLightComponent>(Components[i]);
		}
	}
}

// Called every frame
void AElevatorLightV2AI::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

