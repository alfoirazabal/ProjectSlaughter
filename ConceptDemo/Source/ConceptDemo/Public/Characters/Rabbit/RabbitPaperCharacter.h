// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ConceptDemoPaperCharacter.h"
#include "RabbitPaperCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CONCEPTDEMO_API ARabbitPaperCharacter : public AConceptDemoPaperCharacter
{
	GENERATED_BODY()

	uint8 SequentialTimesJumped;
	
public:
	ARabbitPaperCharacter();
	UPROPERTY(EditAnywhere) uint8 SequentialJumps;

	virtual void BeginPlay() override;
	virtual void DropGun() override;
	virtual void Fire() override;
	virtual void Landed(const FHitResult& Hit) override;
	virtual void Jump() override;
	virtual bool CanJumpInternal_Implementation() const override;
	virtual void UsePower() override;

protected:
	UFUNCTION() void SpawnPowerUpReadyIndicator();
	
};
