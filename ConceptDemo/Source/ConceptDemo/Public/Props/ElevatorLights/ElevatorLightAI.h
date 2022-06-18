// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/PointLightComponent.h>
#include "ElevatorLightAI.generated.h"

UCLASS()
class CONCEPTDEMO_API AElevatorLightAI final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevatorLightAI();

	UPROPERTY(EditAnywhere) bool bRedLightOn;
	UPROPERTY(EditAnywhere) bool bYellowLightOn;
	UPROPERTY(EditAnywhere) bool bGreenLightOn;

	UPointLightComponent* RedLight;
	UPointLightComponent* YellowLight;
	UPointLightComponent* GreenLight;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
