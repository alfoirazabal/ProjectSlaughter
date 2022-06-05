// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeathIndicator.generated.h"

UCLASS()
class CONCEPTDEMO_API ADeathIndicator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADeathIndicator();

	UPROPERTY() ACharacter* DeadCharacter;
	UPROPERTY(EditAnywhere) float DisplayTime;
	UPROPERTY(EditAnywhere) float PlayerMoveXDistance;
	UPROPERTY(EditAnywhere) float PlayerMoveYDistance;
	UPROPERTY(EditAnywhere) float SpawnXDistance;
	UPROPERTY(EditAnywhere) float SpawnYDistance;

	void Disappear();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY() AController* PlayerController;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
