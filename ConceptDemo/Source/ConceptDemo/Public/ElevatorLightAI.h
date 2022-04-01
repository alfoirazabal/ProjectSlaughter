// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/PointLightComponent.h>
#include "ElevatorPlatform.h"
#include "ElevatorLightAI.generated.h"

UCLASS()
class CONCEPTDEMO_API AElevatorLightAI : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevatorLightAI();

	UPROPERTY(EditAnywhere) bool redLightOn;
	UPROPERTY(EditAnywhere) bool yellowLightOn;
	UPROPERTY(EditAnywhere) bool greenLightOn;
	UPROPERTY(EditDefaultsOnly) AElevatorPlatform* elevatorPlatform;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPointLightComponent* redLight;
	UPointLightComponent* yellowLight;
	UPointLightComponent* greenLight;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
