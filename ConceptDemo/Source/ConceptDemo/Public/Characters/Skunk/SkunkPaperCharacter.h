// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConceptDemoPaperCharacter.h"
#include "FartCloud.h"
#include "SkunkPaperCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CONCEPTDEMO_API ASkunkPaperCharacter : public AUConceptDemoPaperCharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TSubclassOf<AFartCloud> SkunkFartCloud;

public:
	ASkunkPaperCharacter();
	virtual void Fire() override;
	virtual void UsePower() override;
	virtual void DropGun() override;
	virtual void Tick(float DeltaTime) override;
	
};
