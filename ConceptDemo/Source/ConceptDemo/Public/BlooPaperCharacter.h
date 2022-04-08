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

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeginOverlapEvent);

	UFUNCTION() void UpdateHealthIndicator() const;
	UFUNCTION() void Respawn();
	UFUNCTION(BlueprintCallable) void HandleMovement(float ScaleValue);
	UFUNCTION(BlueprintCallable) void HandleJump();
	UFUNCTION(BlueprintCallable) void HandleStopJump();
	UFUNCTION() void AttachGun(AGun* Gun);
	UFUNCTION(BlueprintCallable) void DropGun();
	UFUNCTION() bool HasGun();
	UFUNCTION(BlueprintCallable) void Fire();
	UFUNCTION() void TakeDamage(float DamageCount);
	UFUNCTION() void Die();

	FVector InitialPosition;

	ABlooPaperCharacter();

	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
	class UCapsuleComponent* TriggerCapsule;
	UFUNCTION() void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
