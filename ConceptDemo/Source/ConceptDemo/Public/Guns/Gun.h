// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.h"
#include "SlaughterFirendsDemoConstants.h"
#include "Gun.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShotLost);

UENUM() enum EGunType
{
	Common,
	Rare,
	Epic
};

UCLASS()
class CONCEPTDEMO_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeginOverlapEvent);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGunDead, AGun*, Gun);
	
	// Sets default values for this actor's properties
	AGun();
	UPROPERTY(EditAnywhere) bool bRotate;
	UPROPERTY(EditAnywhere) uint8 RotationSpeed;
	UPROPERTY(EditAnywhere) uint8 ShotsCount;
	UPROPERTY(EditAnywhere) int32 TimeBetweenShots;
	UPROPERTY(EditAnywhere) float ShotDamage;
	UPROPERTY(EditAnywhere) uint8 CartridgeSize;
	UPROPERTY(EditAnywhere) int32 ReloadTimeInMilliseconds;
	UPROPERTY(EditAnywhere) int32 ShotLossTime;	// Time by which a bullet is lost. If 0 the gun shall be destroyed

	UPROPERTY(EditAnywhere) FVector BulletSpawnRelativeLocation;

	UPROPERTY(EditAnywhere) TSubclassOf<ABullet> BulletClass;

	UPROPERTY() TEnumAsByte<EGunType> GunType;

	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
	class UCapsuleComponent* TriggerCapsule;

	FVector InitialLocation;
	EFacing_Direction FacingDirection;
	int32 ShotsLeft;

	FOnShotLost ShotLost;
	FOnGunDead GunDead;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int32 CurrentTimeBetweenShots;
	int32 CurrentShotLossTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetAttached();
	void SetDetached();
	UFUNCTION() void Fire();
	UFUNCTION() void Respawn();

};