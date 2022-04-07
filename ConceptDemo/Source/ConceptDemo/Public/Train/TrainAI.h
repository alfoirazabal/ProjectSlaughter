// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrainAI.generated.h"

UCLASS()
class CONCEPTDEMO_API ATrainAI final : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrainAI();

	UPROPERTY(EditAnywhere, BlueprintReadWrite) float speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FVector direction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float maxTravelDistance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float distanceTraveled;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
