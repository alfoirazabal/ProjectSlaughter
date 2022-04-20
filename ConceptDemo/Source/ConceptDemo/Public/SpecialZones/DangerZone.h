// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "DangerZone.generated.h"

/**
 * 
 */
UCLASS()
class CONCEPTDEMO_API ADangerZone : public AStaticMeshActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere) float DamageHitDeltaSeconds;
	UPROPERTY(EditAnywhere) float ZoneDamage;
	float CurrentDamageHitDeltaSeconds;
	
	virtual void Tick(float DeltaSeconds) override;
	
	ADangerZone();
	
};
