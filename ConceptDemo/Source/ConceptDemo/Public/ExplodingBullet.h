// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExplodingBullet.generated.h"

/**
 * 
 */
UCLASS()
class CONCEPTDEMO_API AExplodingBullet : public AActor
{
	GENERATED_BODY()

	AExplodingBullet();
	
	UPROPERTY(EditAnywhere) float DamageRadiusSize;
	UPROPERTY(EditAnywhere) bool DamageDecreasesWithRadius;
	UPROPERTY(EditAnywhere) float InflationSpeed;
	UPROPERTY(EditAnywhere) float ExplosionDamage;
	float InitialDamage;
	float CurrentDamageRadiusSize;

	virtual void Tick(float DeltaSeconds) override;
	
};
