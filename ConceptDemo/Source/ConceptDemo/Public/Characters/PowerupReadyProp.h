// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerupReadyProp.generated.h"

UCLASS()
class CONCEPTDEMO_API APowerupReadyProp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerupReadyProp();

	UPROPERTY(EditAnywhere) float DisplayTime;
	UPROPERTY() AActor* ActorToFollow;
	UPROPERTY(EditAnywhere) FVector SpawnActorRelativeLocation;

	UFUNCTION() void Disappear();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
