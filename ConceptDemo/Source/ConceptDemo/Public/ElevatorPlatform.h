// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElevatorPlatform.generated.h"

UENUM() enum PLATFORM_MOVING_DIRECTION {
	MOVING_UP		UMETA(DisplayName = "Moving Up"),
	MOVING_DOWN		UMETA(DisplayName = "Moving Down")
};

enum PLATFORM_STATUS {
	MOVING		UMETA(DisplayName = "Moving"),
	ON_CEILING	UMETA(DisplayName = "OnTheCeiling"),
	ON_MIDDLE	UMETA(DisplayName = "OnTheMiddle"),
	ON_FLOOR	UMETA(DisplayName = "OnTheFloor")
};

UCLASS()
class CONCEPTDEMO_API AElevatorPlatform : public AActor
{
	GENERATED_BODY()
	
private:
	bool inTheMiddle;
	PLATFORM_STATUS lastStaticStatus;

public:	
	// Sets default values for this actor's properties
	AElevatorPlatform();
	UPROPERTY(EditAnywhere) bool isActivated;
	UPROPERTY(EditAnywhere) float floorLevel;
	UPROPERTY(EditAnywhere) float middleLevel;
	UPROPERTY(EditAnywhere) float ceilingLevel;
	UPROPERTY(EditAnywhere) int stillTime;
	UPROPERTY(EditAnywhere) float speed;

	UPROPERTY(EditAnywhere, Category = "Platform Movement") TEnumAsByte<PLATFORM_MOVING_DIRECTION> MovingDirection;
	TEnumAsByte<PLATFORM_STATUS> PlatformStatus;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	uint8 currentStillTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	PLATFORM_STATUS GetTargetLocation();

};
