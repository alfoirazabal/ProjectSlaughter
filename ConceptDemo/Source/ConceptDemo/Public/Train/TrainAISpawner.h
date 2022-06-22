// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrainAI.h"
#include "Props/ElevatorLights/ElevatorLightAI.h"
#include "SlaughterFirendsDemoConstants.h"
#include "TrainAISpawner.generated.h"

UCLASS()
class CONCEPTDEMO_API ATrainAISpawner final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrainAISpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector direction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float travelSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float maxDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float minSpawnTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float maxSpawnTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) float trainDistanceOnYellowLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) TSubclassOf<ATrainAI> trainClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) AElevatorLightAI* trainTrafficLights;

	UPROPERTY(EditAnywhere) USoundBase* TrainArrivalSound;
	UPROPERTY() UAudioComponent* TrainArrivalSoundComponent;
	UPROPERTY(EditAnywhere) USoundBase* TrainPassingSound;
	UPROPERTY(EditAnywhere) USoundBase* TrainOnStationSound;
	UPROPERTY(EditAnywhere) float TrainOnStationSoundPlayDelayFromYellowLight;

private:
	UFUNCTION() void SetRedLight() const;
	UFUNCTION() void SetYellowLight() const;
	UFUNCTION() void SetGreenLight() const;

	UFUNCTION() void PlayTrainOnStationSound() const;

	UPROPERTY() float redLightOnTime;
	UPROPERTY() float redLightTimeLeft;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnVehicle();

	UPROPERTY() float randSpawnTime;
	UPROPERTY() float currentSpawnTime;

	SlaughterFirendsDemoConstants* demoConstantsHelper;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
