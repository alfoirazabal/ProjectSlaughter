// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "Droppable.generated.h"

UCLASS()
class CONCEPTDEMO_API ADroppable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADroppable();
	
	UPROPERTY(EditAnywhere) float SpawnTime;
	UPROPERTY(EditAnywhere) float RelativeSpriteSize;
	UPROPERTY(EditAnywhere) UPaperSpriteComponent* PaperSpriteComponent;
	UFUNCTION() void Disappear();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
