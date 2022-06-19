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
	
	static ConstructorHelpers::FClassFinder<ASpaceShip> SpaceShip1ClassFinder(TEXT("/Game/Props/Vehicles/SpaceShip_1/SpaceShip_1"));
	static ConstructorHelpers::FClassFinder<ASpaceShip> SpaceShip2ClassFinder(TEXT("/Game/Props/Vehicles/SpaceShip_2_Police/Ship2_Police"));
	this->VehicleTypes.Add(SpaceShip1ClassFinder.Class);
	this->VehicleTypes.Add(SpaceShip2ClassFinder.Class);
	this->VehicleTypesSpawnChances.Add(1);
	this->VehicleTypesSpawnChances.Add(0.05);
}

// Called when the game starts or when spawned
void ASpaceShipSpawner::BeginPlay()
{
	Super::BeginPlay();
	const float RandomSpawnTime = FMath::RandRange(this->SpawnMinTime, this->SpawnMaxTime);
	FTimerHandle TimerHandle;
	
	this->RandomSpaceShipGenerator = NewObject<UObjectWithChanceGenerator>();
	for (int i = 0 ; i < this->VehicleTypes.Num() ; i++)
	{
		TSubclassOf<ASpaceShip> VehicleType = this->VehicleTypes[i];
		if (this->VehicleTypesSpawnChances.Num() == this->VehicleTypes.Num())
		{
			const float SpawnChance = this->VehicleTypesSpawnChances[i];
			this->RandomSpaceShipGenerator->AddClass(VehicleType, SpawnChance);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(783164383, 10, FColor::Red, "You need to have the same amount of spawn chances as there are vehicles: " + this->GetName());
		}
	}
	this->RandomSpaceShipGenerator->BuildSpawnChances();
	
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
	const TSubclassOf<ASpaceShip> RandomSpaceShipType = this->RandomSpaceShipGenerator->GetRandomObjectClass();
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
		const TSubclassOf<ASpaceShip> RandomSpaceShipType = this->RandomSpaceShipGenerator->GetRandomObjectClass();
		if (RandomSpaceShipType)
		{
			ASpaceShip* NewShip = this->GetWorld()->SpawnActorDeferred<ASpaceShip>(RandomSpaceShipType, Transform, this, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
			NewShip->StartupRotation = this->StartupRotation;
			NewShip->TravelVelocity = this->TravelVelocity;
			NewShip->TravelDistance = this->TravelDistance;
			UGameplayStatics::FinishSpawningActor(NewShip, Transform);
			NewShip->SetActorLocation(SpawnPosition);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(783164382, 4, FColor::Red, "No space ship types to spawn on SpaceShipSpawner");
		}
		CurrentSpawnedDistance += RandomSpawnDistance;
	}
}
