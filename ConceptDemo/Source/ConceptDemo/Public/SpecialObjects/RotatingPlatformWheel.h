// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "RotatingPlatformWheel.generated.h"

USTRUCT() struct FPlatformAndPath {
	GENERATED_BODY();
	UPROPERTY() AActor* Platform;
	float PositionOnSpline;
};

UCLASS()
class CONCEPTDEMO_API ARotatingPlatformWheel : public AActor
{
	GENERATED_BODY()

	UPROPERTY() USplineComponent* PlatformWheelPath;
	UPROPERTY(EditAnywhere) TSubclassOf<AActor> PlatformsType;
	UPROPERTY(EditAnywhere) uint8 PlatformsCount;
	UPROPERTY(EditAnywhere) uint8 PlatformsWaitTime;
	UPROPERTY() uint8 CurrentPlatformsWaitTime;
	UPROPERTY() float PlatformsDistanceBeforeWait;	// Distance that needs to be traveled by each platform before waiting.
	UPROPERTY() float CurrentPlatformsDistanceTraveled;	// Current Distance of each platform traveled before needing to wait.
	UPROPERTY() TArray<FPlatformAndPath> PlatformAndPaths;

	UPROPERTY(EditAnywhere) uint8 PlatformMovementSpeed;
	
public:	
	// Sets default values for this actor's properties
	ARotatingPlatformWheel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION() void MovePlatform(FPlatformAndPath& PlatformAndPath) const;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
