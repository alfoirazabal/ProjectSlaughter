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
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool bRotate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 RotationSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 ShotsCount;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 TimeBetweenShotsInMilliseconds;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float ShotDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 CartridgeSize;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 ReloadTimeInMilliseconds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector BulletSpawnRelativeLocation;

	UPROPERTY(EditAnywhere) TSubclassOf<ABullet> BulletClass;

	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
	class UCapsuleComponent* TriggerCapsule;
	UFUNCTION() void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	FVector InitialLocation;
	EFacing_Direction FacingDirection;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetAttached();
	void SetDetached();
	UFUNCTION(BlueprintCallable) void Fire();
	UFUNCTION(BlueprintCallable) void Respawn();

};
