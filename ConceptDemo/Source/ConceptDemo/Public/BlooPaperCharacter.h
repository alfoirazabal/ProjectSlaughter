// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include <PaperFlipbook.h>
#include "SlaughterFirendsDemoConstants.h"
#include "BlooPaperCharacter.generated.h"

UCLASS()
class CONCEPTDEMO_API ABlooPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()

private:
	void MoveGun();

protected:
	UPaperFlipbook* idleFlipbook;
	UPaperFlipbook* movingFlipbook;
	UPaperFlipbook* jumpingFlipbook;
	AGun* attachedGun;
	FACING_DIRECTION facingDirection;
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable) virtual void HandleMovement(float scaleValue);
	UFUNCTION(BlueprintCallable) virtual void HandleJump();
	UFUNCTION(BlueprintCallable) virtual void HandleStopJump();
	UFUNCTION(BlueprintCallable) virtual void AttachGun(AGun* gun);
	UFUNCTION(BlueprintCallable) virtual void Fire();

	FVector initialPosition;

	ABlooPaperCharacter();

};
