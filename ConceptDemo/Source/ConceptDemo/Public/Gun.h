// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.h"
#include "SlaughterFirendsDemoConstants.h"
#include "Gun.generated.h"

UCLASS()
class CONCEPTDEMO_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool rotate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 rotationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 shotsCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 timeBetweenShotsInMilliseconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float shotDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 cartridgeSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 reloadTimeInMilliseconds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector bulletSpawnRelativeLocation;

	UPROPERTY(EditAnywhere) TSubclassOf<ABullet> bulletClass;

	FACING_DIRECTION facingDirection;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void SetAttached();
	UFUNCTION(BlueprintCallable) virtual void Fire();

};
