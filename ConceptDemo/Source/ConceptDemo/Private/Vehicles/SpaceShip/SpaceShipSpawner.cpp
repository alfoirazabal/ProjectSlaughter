// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicles/SpaceShip/SpaceShipSpawner.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
ASpaceShipSpawner::ASpaceShipSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->StartWithSpawnedVehicles = true;
	this->TravelVelocity = 500;
	this->TravelDistance = 3750;
	this->SpawnMinTime = 3;
	this->SpawnMaxTime = 8;
}

// Called when the game starts or when spawned
void ASpaceShipSpawner::BeginPlay()
{
	Super::BeginPlay();
	const float RandomSpawnTime = FMath::RandRange(this->SpawnMinTime, this->SpawnMaxTime);
	FTimerHandle TimerHandle;
	this->GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASpaceShipSpawner::SpawnVehicle, RandomSpawnTime, false);
	if (this->StartWithSpawnedVehicles) 
	{
		this->SpawnStartupVehicles();
	}
}

// Called every frame
void ASpaceShipSpawner::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpaceShipSpawner::SpawnVehicle()
{
	const FTransform Transform = this->GetActorTransform();
	ASpaceShip* NewShip = this->GetWorld()->SpawnActorDeferred<ASpaceShip>(this->VehicleType, Transform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	NewShip->StartupRotation = this->StartupRotation;
	NewShip->TravelVelocity = this->TravelVelocity;
	NewShip->TravelDistance = this->TravelDistance;
	UGameplayStatics::FinishSpawningActor(NewShip, Transform);
	const float RandomSpawnTime = FMath::RandRange(this->SpawnMinTime, this->SpawnMaxTime);
	FTimerHandle TimerHandle;
	this->GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASpaceShipSpawner::SpawnVehicle, RandomSpawnTime, false);
}

void ASpaceShipSpawner::SpawnStartupVehicles() 
{
	float CurrentSpawnedDistance = 0;
	while (
		(this->TravelVelocity > 0 && CurrentSpawnedDistance <= this->TravelDistance) ||
		(this->TravelVelocity < 0 && CurrentSpawnedDistance >= -this->TravelDistance)
	)
	{
		const float RandomSpawnDistance = (FMath::RandRange(this->SpawnMinTime, this->SpawnMaxTime) * this->TravelVelocity) + CurrentSpawnedDistance;
		FVector SpawnPosition = this->GetActorLocation();
		SpawnPosition.Y += RandomSpawnDistance;
		const FTransform Transform = this->GetActorTransform();
		ASpaceShip* NewShip = this->GetWorld()->SpawnActorDeferred<ASpaceShip>(this->VehicleType, Transform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		NewShip->StartupRotation = this->StartupRotation;
		NewShip->TravelVelocity = this->TravelVelocity;
		NewShip->TravelDistance = this->TravelDistance;
		UGameplayStatics::FinishSpawningActor(NewShip, Transform);
		NewShip->SetActorLocation(SpawnPosition);
		CurrentSpawnedDistance += RandomSpawnDistance;
	}
	
}
