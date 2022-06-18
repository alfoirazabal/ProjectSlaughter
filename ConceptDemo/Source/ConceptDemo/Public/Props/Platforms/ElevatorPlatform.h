// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ElevatorPlatform.generated.h"

UENUM() enum EPlatform_Moving_Direction {
	Moving_Up		UMETA(DisplayName = "Moving Up"),
	Moving_Down		UMETA(DisplayName = "Moving Down")
};

enum EPlatform_Status {
	Moving		UMETA(DisplayName = "Moving"),
	On_Ceiling	UMETA(DisplayName = "OnTheCeiling"),
	On_Middle	UMETA(DisplayName = "OnTheMiddle"),
	On_Floor	UMETA(DisplayName = "OnTheFloor")
};

UCLASS()
class CONCEPTDEMO_API AElevatorPlatform final : public AActor
{
	GENERATED_BODY()
	
private:
	bool bInTheMiddle;
	EPlatform_Status LastStaticStatus;

public:	
	// Sets default values for this actor's properties
	AElevatorPlatform();
	UPROPERTY(EditAnywhere) bool bIsActivated;
	UPROPERTY(EditAnywhere) float FloorLevel;
	UPROPERTY(EditAnywhere) float MiddleLevel;
	UPROPERTY(EditAnywhere) float CeilingLevel;
	UPROPERTY(EditAnywhere) int StillTime;
	UPROPERTY(EditAnywhere) float Speed;

	UPROPERTY(EditAnywhere, Category = "Platform Movement") TEnumAsByte<EPlatform_Moving_Direction> MovingDirection;
	TEnumAsByte<EPlatform_Status> PlatformStatus;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	uint8 CurrentStillTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	EPlatform_Status GetTargetLocation() const;

};
