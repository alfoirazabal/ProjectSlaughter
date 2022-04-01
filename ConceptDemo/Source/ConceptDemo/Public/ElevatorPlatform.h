// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElevatorPlatform.generated.h"

UCLASS()
class CONCEPTDEMO_API AElevatorPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevatorPlatform();
	UPROPERTY(BlueprintReadWrite, EditAnywhere) bool isActivated;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float floorLevel;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) float ceilingLevel;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) int stillTime;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) int speed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	uint8 currentStillTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
