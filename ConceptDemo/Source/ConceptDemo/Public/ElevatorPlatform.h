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
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere) bool isActivated;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere) float floorLevel;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere) float ceilingLevel;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere) uint8 speed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
