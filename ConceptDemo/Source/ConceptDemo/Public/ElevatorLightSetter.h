// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElevatorLightV2AI.h"
#include "ElevatorPlatform.h"
#include "ElevatorLightSetter.generated.h"

UCLASS()
class CONCEPTDEMO_API AElevatorLightSetter final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevatorLightSetter();

	UPROPERTY(EditAnywhere) AElevatorLightV2AI* ElevatorLight;
	UPROPERTY(EditAnywhere) AElevatorPlatform* ElevatorPlatform;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
