// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ConceptDemoPaperPawn.h"
#include "GameFramework/Actor.h"
#include "DeathIndicator.generated.h"

UCLASS()
class CONCEPTDEMO_API ADeathIndicator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADeathIndicator();

	UPROPERTY() AConceptDemoPaperPawn* DeadCharacter;
	UPROPERTY(EditAnywhere) float DisplayTime;
	UPROPERTY(EditAnywhere) float PlayerMoveXDistance;
	UPROPERTY(EditAnywhere) float PlayerMoveYDistance;
	UPROPERTY(EditAnywhere) float SpawnXDistance;
	UPROPERTY(EditAnywhere) float SpawnYDistance;
	UPROPERTY(EditAnywhere) float PlayerMoveXOnDestroyDistance;
	UPROPERTY(EditAnywhere) float PlayerMoveYOnDestroyDistance;

	void Disappear();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY() AController* PlayerController;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
