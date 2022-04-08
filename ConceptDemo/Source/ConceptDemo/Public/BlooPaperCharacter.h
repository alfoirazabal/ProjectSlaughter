// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ConceptDemoPaperCharacter.h"
#include "BlooPaperCharacter.generated.h"

UCLASS()
class CONCEPTDEMO_API ABlooPaperCharacter final : public AUConceptDemoPaperCharacter
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:

	ABlooPaperCharacter();
	
};
