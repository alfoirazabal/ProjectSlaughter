// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include <PaperFlipbook.h>
#include "BlooPaperCharacter.generated.h"

/**
 * 
 */
UCLASS()
class CONCEPTDEMO_API ABlooPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()

protected:
	UPaperFlipbook* idleFlipbook;
	UPaperFlipbook* movingFlipbook;
	UPaperFlipbook* jumpingFlipbook;

public:
	UFUNCTION(BlueprintCallable) virtual void HandleMovement(float scaleValue);
	UFUNCTION(BlueprintCallable) virtual void HandleJump();
	UFUNCTION(BlueprintCallable) virtual void HandleStopJump();

	ABlooPaperCharacter();

};
