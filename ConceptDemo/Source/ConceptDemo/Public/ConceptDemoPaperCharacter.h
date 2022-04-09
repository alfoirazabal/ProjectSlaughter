// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <PaperFlipbook.h>

#include "BlooHealthHUD.h"
#include "Gun.h"
#include "PaperCharacter.h"
#include "ConceptDemoPaperCharacter.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CONCEPTDEMO_API AUConceptDemoPaperCharacter : public APaperCharacter
{
	GENERATED_BODY()

	void MoveGun() const;

	void CheckCharacterFall();
	void EnsureXAxisLocation();
	bool IsOnTheAir() const;
	static FRotator GetRightRotator();
	static FRotator GetLeftRotator();

	bool bFallingDeath;

public:	
	// Sets default values for this component's properties
	AUConceptDemoPaperCharacter();

protected:
	// Called when the game starts
	UPROPERTY(EditAnywhere, Category="Concept Demo Action Sprites") UPaperFlipbook* IdleFlipBook;
	UPROPERTY(EditAnywhere, Category="Concept Demo Action Sprites") UPaperFlipbook* MovingFlipBook;
	UPROPERTY(EditAnywhere, Category="Concept Demo Action Sprites") UPaperFlipbook* JumpingFlipBook;
	UPROPERTY(EditAnywhere, Category="Character Asset Positions") int GunZRelativeLocation;
	
	UPROPERTY() AGun* AttachedGun;
	EFacing_Direction FacingDirection;
	UPROPERTY() TArray<AGun*> GunsIgnored;
	UPROPERTY() UBlooHealthHUD* HealthHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 Lives;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float LifeSize;

	UPROPERTY(BlueprintReadWrite) uint8 CurrentLives;
	UPROPERTY(BlueprintReadWrite) float CurrentLifeSize;
	virtual void BeginPlay() override;
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
	UFUNCTION() bool HasGun() const;
	UFUNCTION(BlueprintCallable) void Fire();
	UFUNCTION() void TakeDamage(float DamageCount);
	UFUNCTION() void Die();

	FVector InitialPosition;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
	class UCapsuleComponent* TriggerCapsule;
	UFUNCTION() void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
};
