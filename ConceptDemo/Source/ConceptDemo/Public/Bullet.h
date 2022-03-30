// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UENUM()
enum FACING_DIRECTION {
	RIGHT	UMETA(DisplayName = "Right"),
	LEFT	UMETA(DisplayName = "Left")
};

UCLASS()
class CONCEPTDEMO_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	UPROPERTY(BlueprintReadWrite, EditAnywhere) TEnumAsByte<FACING_DIRECTION> FacingDirection;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) uint8 TravelSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) int MaxTravelDistance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector initialPosition;
	float totalDistanceTraveled;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};