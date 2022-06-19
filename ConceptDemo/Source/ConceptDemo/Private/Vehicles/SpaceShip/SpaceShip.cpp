// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicles/SpaceShip/SpaceShip.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASpaceShip::ASpaceShip()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->SpawnChance = 1;
}

// Called when the game starts or when spawned
void ASpaceShip::BeginPlay()
{
	Super::BeginPlay();
	this->SetActorRotation(this->StartupRotation);
}

// Called every frame
void ASpaceShip::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	const FVector CurrentLocation = this->GetActorLocation();
	float TravelSpeed = this->TravelVelocity * DeltaTime;
	const FVector NewLocation = CurrentLocation + FVector(0, TravelSpeed, 0);
	this->SetActorLocation(NewLocation);
	const float TraveledDistance = FVector::Dist(NewLocation, CurrentLocation);
	this->CurrentTravelDistance += UKismetMathLibrary::Abs(TravelSpeed);
	if (this->CurrentTravelDistance >= this->TravelDistance)
	{
		this->Destroy();
	}
}

