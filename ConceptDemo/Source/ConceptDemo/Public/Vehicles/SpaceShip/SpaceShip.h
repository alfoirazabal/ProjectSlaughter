// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceShip.generated.h"

UCLASS()
class CONCEPTDEMO_API ASpaceShip : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpaceShip();
	
	UPROPERTY(EditAnywhere) FRotator StartupRotation;
	UPROPERTY(EditAnywhere) float TravelVelocity;
	UPROPERTY(EditAnywhere) float TravelDistance;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY() float CurrentTravelDistance;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
