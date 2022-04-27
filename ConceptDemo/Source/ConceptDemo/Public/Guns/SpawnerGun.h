// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gun.h"
#include "GameFramework/Actor.h"
#include "SpawnerGun.generated.h"

UCLASS()
class CONCEPTDEMO_API ASpawnerGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnerGun();

	UPROPERTY(EditAnywhere) TEnumAsByte<ESpawnChance> GunSpawnRarity;
	UPROPERTY() bool InUse;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
