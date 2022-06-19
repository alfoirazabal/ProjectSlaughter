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
	this->FillRandomVehicleTypes();
	this->GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASpaceShipSpawner::SpawnVehicle, RandomSpawnTime, false);
	if (this->StartWithSpawnedVehicles) 
	{
		this->SpawnStartupVehicles();
	}
}

void ASpaceShipSpawner::FillRandomVehicleTypes()
{
	float VehicleTypesProbabilitySum = 0;
	TArray<ASpaceShip*> RandomVehicles;
	for (int i = 0 ; i < this->VehicleTypes.Num() ; i++)
	{
		const TSubclassOf<ASpaceShip> CurrentVehicleType = this->VehicleTypes[i];
		ASpaceShip* CurrentRandomVehicle = Cast<ASpaceShip>(CurrentVehicleType->GetDefaultObject());
		if (CurrentRandomVehicle)
		{
			VehicleTypesProbabilitySum += CurrentRandomVehicle->SpawnChance;
			RandomVehicles.Add(CurrentRandomVehicle);
		}
	}
	this->RandomVehicleTypes.Reserve(100);
	for (int i = 0 ; i < 100 ; i++)
	{
		for (int j = 0 ; j < RandomVehicles.Num() ; j++)
		{
			const int TimesToAdd = (RandomVehicles[j]->SpawnChance / VehicleTypesProbabilitySum) * 100;
			for (int k = i ; k < TimesToAdd + i ; k++)
			{
				RandomVehicleTypes.Add(this->VehicleTypes[j]);
			}
		}
	}
}

// Called every frame
void ASpaceShipSpawner::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TSubclassOf<ASpaceShip> ASpaceShipSpawner::GetRandomSpaceShipType()
{
	TSubclassOf<ASpaceShip> RandomVehicleType = nullptr;
	if (this->RandomVehicleTypes.Num() > 0)
	{
		const int RandomPosition = FMath::RandRange(0, 100);
		RandomVehicleType = this->RandomVehicleTypes[RandomPosition];
	}
	return RandomVehicleType;
}

void ASpaceShipSpawner::SpawnVehicle()
{
	const FTransform Transform = this->GetActorTransform();
	const TSubclassOf<ASpaceShip> RandomSpaceShipType = this->GetRandomSpaceShipType();
	if (RandomSpaceShipType)
	{
		ASpaceShip* NewShip = this->GetWorld()->SpawnActorDeferred<ASpaceShip>(RandomSpaceShipType, Transform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		NewShip->StartupRotation = this->StartupRotation;
		NewShip->TravelVelocity = this->TravelVelocity;
		NewShip->TravelDistance = this->TravelDistance;
		UGameplayStatics::FinishSpawningActor(NewShip, Transform);
		const float RandomSpawnTime = FMath::RandRange(this->SpawnMinTime, this->SpawnMaxTime);
		FTimerHandle TimerHandle;
		this->GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASpaceShipSpawner::SpawnVehicle, RandomSpawnTime, false);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(783164382, 4, FColor::Red, "No space ship types to spawn on SpaceShipSpawner");
	}
}

void ASpaceShipSpawner::SpawnStartupVehicles() 
{
	if (this->RandomVehicleTypes.Num() > 0)
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
			const TSubclassOf<ASpaceShip> RandomSpaceShipType = this->GetRandomSpaceShipType();
			ASpaceShip* NewShip = this->GetWorld()->SpawnActorDeferred<ASpaceShip>(RandomSpaceShipType, Transform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
			NewShip->StartupRotation = this->StartupRotation;
			NewShip->TravelVelocity = this->TravelVelocity;
			NewShip->TravelDistance = this->TravelDistance;
			UGameplayStatics::FinishSpawningActor(NewShip, Transform);
			NewShip->SetActorLocation(SpawnPosition);
			CurrentSpawnedDistance += RandomSpawnDistance;
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(783164382, 4, FColor::Red, "No space ship types to spawn on SpaceShipSpawner");
	}
}
