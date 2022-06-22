// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LifeCollectible.generated.h"

UCLASS()
class CONCEPTDEMO_API ALifeCollectible : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALifeCollectible();

	UPROPERTY(EditAnywhere) float LifeBarFill;
	UPROPERTY(EditAnywhere) float SpawnTime;
	UPROPERTY(EditAnywhere) float RotationSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void SpawnTimeExpired();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
	class UCapsuleComponent* TriggerCapsule;
	UFUNCTION() void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
