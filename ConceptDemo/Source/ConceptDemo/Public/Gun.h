// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.h"
#include "SlaughterFirendsDemoConstants.h"
#include "Gun.generated.h"

UCLASS()
class CONCEPTDEMO_API AGun final : public AActor
{
	GENERATED_BODY()
	
public:	

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeginOverlapEvent);
	
	// Sets default values for this actor's properties
	AGun();
	UPROPERTY(EditAnywhere) bool bRotate;
	UPROPERTY(EditAnywhere) uint8 RotationSpeed;
	UPROPERTY(EditAnywhere) uint8 ShotsCount;
	UPROPERTY(EditAnywhere) int32 TimeBetweenShots;
	UPROPERTY(EditAnywhere) float ShotDamage;
	UPROPERTY(EditAnywhere) uint8 CartridgeSize;
	UPROPERTY(EditAnywhere) int32 ReloadTimeInMilliseconds;

	UPROPERTY(EditAnywhere) FVector BulletSpawnRelativeLocation;

	UPROPERTY(EditAnywhere) TSubclassOf<ABullet> BulletClass;

	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
	class UCapsuleComponent* TriggerCapsule;

	FVector InitialLocation;
	EFacing_Direction FacingDirection;
	int32 ShotsLeft;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int32 CurrentTimeBetweenShots;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetAttached();
	void SetDetached();
	UFUNCTION() void Fire();
	UFUNCTION() void Respawn();

};
