// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlaughterFirendsDemoConstants.h"
#include "Bullet.generated.h"

UCLASS()
class CONCEPTDEMO_API ABullet final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	UPROPERTY(BlueprintReadWrite, EditAnywhere) TEnumAsByte<EFacing_Direction> FacingDirection;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) uint8 TravelSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) int MaxTravelDistance;

	UPROPERTY() AActor* FireSource;

	float BulletDamage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector InitialPosition;
	float TotalDistanceTraveled;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
