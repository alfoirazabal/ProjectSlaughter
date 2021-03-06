// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ConceptDemoPaperCharacter.h"
#include "HedgeThorn.h"
#include "HedgePaperCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CONCEPTDEMO_API AHedgePaperCharacter : public AConceptDemoPaperCharacter
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere) TSubclassOf<AHedgeThorn> HedgeThornType;
	UPROPERTY(EditAnywhere, Category="Sounds") USoundBase* HedgeThornSound;
	UPROPERTY(EditAnywhere) float ThornSpawnDistance;
	UPROPERTY(EditAnywhere) float ThornDamage;

public:
	AHedgePaperCharacter();
	virtual void Fire() override;
	virtual void UsePower() override;
	virtual void DropGun() override;
	virtual void Tick(float DeltaTime) override;

};