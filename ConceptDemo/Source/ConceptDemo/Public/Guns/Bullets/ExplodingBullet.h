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

public:
	
	AExplodingBullet();
	
	UPROPERTY(EditAnywhere) float DamageRadiusSize;
	UPROPERTY(EditAnywhere) bool DamageDecreasesWithRadius;
	UPROPERTY(EditAnywhere) float InflationSpeed;
	UPROPERTY(EditAnywhere) float ExplosionDamage;
	UPROPERTY(EditAnywhere) USoundBase* ExplosionSound;
	UPROPERTY() AActor* SourceActor;
	UPROPERTY() TArray<AActor*> AffectedActors;
	float InitialDamage;
	float CurrentDamageRadiusSize;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
	class UCapsuleComponent* TriggerCapsule;
	UFUNCTION() void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
