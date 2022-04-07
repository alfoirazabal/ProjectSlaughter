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

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeginOverlapEvent);
	
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

	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
	class UCapsuleComponent* TriggerCapsule;
	UFUNCTION() void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	FVector initialLocation;
	FACING_DIRECTION facingDirection;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void SetAttached();
	virtual void SetDetached();
	UFUNCTION(BlueprintCallable) virtual void Fire();
	UFUNCTION(BlueprintCallable) void Respawn();

};
