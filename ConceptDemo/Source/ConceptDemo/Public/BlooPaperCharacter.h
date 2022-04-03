// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include <PaperFlipbook.h>
#include <BlooHealthHUD.h>
#include "Components/WidgetComponent.h"
#include "SlaughterFirendsDemoConstants.h"
#include "BlooPaperCharacter.generated.h"

UCLASS()
class CONCEPTDEMO_API ABlooPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()

private:
	void MoveGun();

	void CheckCharacterFall();

protected:
	UPaperFlipbook* idleFlipbook;
	UPaperFlipbook* movingFlipbook;
	UPaperFlipbook* jumpingFlipbook;
	AGun* attachedGun;
	FACING_DIRECTION facingDirection;
	TArray<AGun*> gunsIgnored;
	UBlooHealthHUD* blooHealthHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 lives;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float lifeSize;

	UPROPERTY(BlueprintReadWrite) uint8 currentLives;
	UPROPERTY(BlueprintReadWrite) float currentLifeSize;

	virtual void BeginPlay() override;
	virtual void Tick(float deltaSeconds) override;

public:

	UFUNCTION() void UpdateHealthIndicator();
	UFUNCTION(BlueprintCallable) virtual void Respawn();
	UFUNCTION(BlueprintCallable) virtual void HandleMovement(float scaleValue);
	UFUNCTION(BlueprintCallable) virtual void HandleJump();
	UFUNCTION(BlueprintCallable) virtual void HandleStopJump();
	UFUNCTION(BlueprintCallable) virtual void AttachGun(AGun* gun);
	UFUNCTION(BlueprintCallable) virtual void DropGun();
	UFUNCTION(BlueprintCallable) virtual bool HasGun();
	UFUNCTION(BlueprintCallable) virtual void Fire();
	UFUNCTION(BlueprintCallable) virtual void TakeDamage(float damageCount);
	UFUNCTION(BlueprintCallable) virtual void Die();

	FVector initialPosition;

	ABlooPaperCharacter();

};
