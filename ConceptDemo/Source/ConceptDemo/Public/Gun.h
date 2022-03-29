// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void FaceRight();
	virtual void FaceLeft();
	virtual void SetAttached();

};
