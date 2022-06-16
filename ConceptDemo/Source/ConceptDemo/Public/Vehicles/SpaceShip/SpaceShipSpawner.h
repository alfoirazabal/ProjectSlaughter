// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpaceShip.h"
#include "GameFramework/Actor.h"
#include "SpaceShipSpawner.generated.h"

UCLASS()
class CONCEPTDEMO_API ASpaceShipSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpaceShipSpawner();

	UPROPERTY(EditAnywhere) bool StartWithSpawnedVehicles;
	UPROPERTY(EditAnywhere) FRotator StartupRotation;
	UPROPERTY(EditAnywhere) float TravelVelocity;
	UPROPERTY(EditAnywhere) float TravelDistance;
	UPROPERTY(EditAnywhere) TSubclassOf<ASpaceShip> VehicleType;
	UPROPERTY(EditAnywhere) float SpawnMinTime;
	UPROPERTY(EditAnywhere) float SpawnMaxTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnVehicle();
	void SpawnStartupVehicles();
};