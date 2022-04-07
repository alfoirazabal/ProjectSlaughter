// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/PointLightComponent.h>
#include "ElevatorLightV2AI.generated.h"

UCLASS()
class CONCEPTDEMO_API AElevatorLightV2AI final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevatorLightV2AI();

	UPointLightComponent* SpikesRedLight;
	UPointLightComponent* YellowUpLight;
	UPointLightComponent* YellowDownLight;
	UPointLightComponent* MiddleGreenLight;
	UPointLightComponent* SubwayRedLight;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
