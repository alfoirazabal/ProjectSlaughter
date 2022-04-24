// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Skull.generated.h"

UCLASS()
class CONCEPTDEMO_API ASkull : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASkull();

	uint8 SpawnXDistance;
	uint16 DisappearanceTimeLeft;
	UPROPERTY(EditAnywhere) uint16 DisappearanceTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
