// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include <PaperFlipbook.h>
#include <BlooHealthHUD.h>

#include "Gun.h"
#include "Components/WidgetComponent.h"
#include "SlaughterFirendsDemoConstants.h"
#include "BlooPaperCharacter.generated.h"

UCLASS()
class CONCEPTDEMO_API ABlooPaperCharacter final : public APaperCharacter
{
	GENERATED_BODY()

private:
	void MoveGun() const;

	void CheckCharacterFall();
	void EnsureXAxisLocation();

	bool bFallingDeath;

protected:
	UPROPERTY() UPaperFlipbook* IdleFlipBook;
	UPROPERTY() UPaperFlipbook* MovingFlipBook;
	UPROPERTY() UPaperFlipbook* JumpingFlipBook;
	UPROPERTY() AGun* AttachedGun;
	EFacing_Direction FacingDirection;
	UPROPERTY() TArray<AGun*> GunsIgnored;
	UPROPERTY() UBlooHealthHUD* BlooHealthHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 Lives;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float LifeSize;

	UPROPERTY(BlueprintReadWrite) uint8 CurrentLives;
	UPROPERTY(BlueprintReadWrite) float CurrentLifeSize;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void MakeFallingDeath();

public:

	UFUNCTION() void UpdateHealthIndicator() const;
	UFUNCTION(BlueprintCallable) void Respawn();
	UFUNCTION(BlueprintCallable) void HandleMovement(float ScaleValue);
	UFUNCTION(BlueprintCallable) void HandleJump();
	UFUNCTION(BlueprintCallable) void HandleStopJump();
	UFUNCTION(BlueprintCallable) void AttachGun(AGun* Gun);
	UFUNCTION(BlueprintCallable) void DropGun();
	UFUNCTION(BlueprintCallable) bool HasGun();
	UFUNCTION(BlueprintCallable) void Fire();
	UFUNCTION(BlueprintCallable) void TakeDamage(float DamageCount);
	UFUNCTION(BlueprintCallable) void Die();

	FVector InitialPosition;

	ABlooPaperCharacter();

};
