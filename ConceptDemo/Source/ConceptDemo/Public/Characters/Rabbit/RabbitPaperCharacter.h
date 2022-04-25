// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConceptDemoPaperCharacter.h"
#include "RabbitPaperCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CONCEPTDEMO_API ARabbitPaperCharacter : public AUConceptDemoPaperCharacter
{
	GENERATED_BODY()

	uint8 SequentialTimesJumped;
	
public:
	ARabbitPaperCharacter();
	UPROPERTY(EditAnywhere) uint8 SequentialJumps;
	virtual void Landed(const FHitResult& Hit) override;
	virtual void Jump() override;
	virtual bool CanJumpInternal_Implementation() const override;
	
};
