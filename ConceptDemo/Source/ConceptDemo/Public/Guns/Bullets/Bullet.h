// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExplodingBullet.h"
#include "GameFramework/Actor.h"
#include "SlaughterFirendsDemoConstants.h"
#include "Bullet.generated.h"

UCLASS()
class CONCEPTDEMO_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	UPROPERTY(BlueprintReadWrite, EditAnywhere) TEnumAsByte<EFacing_Direction> FacingDirection;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) uint8 TravelSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere) int MaxTravelDistance;
	UPROPERTY(EditAnywhere) TSubclassOf<AExplodingBullet> ExplodingBulletClass;
	UPROPERTY(EditAnywhere) USoundBase* ShotSound;
	UPROPERTY() UAudioComponent* ShotSoundComponent;

	UPROPERTY() AActor* SourceActor;
	UPROPERTY() AActor* TargetDamagedActor;
	UPROPERTY() AActor* SourceGun;

	UPROPERTY(EditAnywhere) float BulletDamage;
	UPROPERTY(EditAnywhere) float BulletScoreMultiplier; // Score to give to shooter based on BulletDamage

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FVector InitialPosition;
	float TotalDistanceTraveled;
	bool ExplodingBullet;

public:	

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeginOverlapEvent);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION() void DestroyOrExplodeBullet();
	
	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
	class UCapsuleComponent* TriggerCapsule;
	UFUNCTION() void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
