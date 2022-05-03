// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <PaperFlipbook.h>

#include "Guns/Gun.h"
#include "PaperCharacter.h"
#include "PaperCharacterHUD.h"
#include "Characters/Skull.h"
#include "ConceptDemoPaperCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeath);

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

	UPROPERTY(EditAnywhere) UTexture2D* CharacterImage;
	UPROPERTY(EditAnywhere) FString PlayerDescription;

protected:
	// Called when the game starts
	UPROPERTY(EditAnywhere, Category="Concept Demo Action Sprites") UPaperFlipbook* IdleFlipBook;
	UPROPERTY(EditAnywhere, Category="Concept Demo Action Sprites") UPaperFlipbook* MovingFlipBook;
	UPROPERTY(EditAnywhere, Category="Concept Demo Action Sprites") UPaperFlipbook* JumpingFlipBook;
	UPROPERTY(EditAnywhere, Category="Concept Demo Drops") TSubclassOf<ASkull> DeathSkull;
	UPROPERTY(EditAnywhere, Category="Character Asset Positions") int GunZRelativeLocation;

	UPROPERTY(EditAnywhere, Category="Sounds") USoundBase* JumpSound;
	UPROPERTY(EditAnywhere, Category="Sounds") USoundBase* PowerSound;
	UPROPERTY(EditAnywhere, Category="Sounds") USoundBase* DamageReceivedSound;
	
	UPROPERTY(EditAnywhere) FText PlayerName;
	
	EFacing_Direction FacingDirection;
	UPROPERTY() TArray<AGun*> GunsIgnored;
	UPROPERTY() UPaperCharacterHUD* CharacterHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 Lives;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float LifeSize;

	UPROPERTY(BlueprintReadWrite) uint8 CurrentLives;
	UPROPERTY(BlueprintReadWrite) float CurrentLifeSize;
	
	UPROPERTY(EditAnywhere) uint16 SpecialPowerLoadTime;
	uint16 CurrentSpecialPowerLoadTime;
	
	virtual void BeginPlay() override;
	void MakeFallingDeath();

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeginOverlapEvent);

	UFUNCTION() void SetPlayerName(FText NewPlayerName) const;
	UFUNCTION() void UpdateHealthIndicator() const;
	UFUNCTION() void Respawn();
	UFUNCTION(BlueprintCallable) void HandleMovement(float ScaleValue);
	UFUNCTION(BlueprintCallable) void DropDown();
	virtual void Jump() override;
	UFUNCTION() void AttachGun(AGun* Gun);
	UFUNCTION(BlueprintCallable) virtual void DropGun();
	UFUNCTION() bool HasGun() const;
	UFUNCTION(BlueprintCallable) virtual void Fire();
	UFUNCTION() virtual void UsePower();
	UFUNCTION() void UpdateShotsCount();
	UFUNCTION() void TakeDamage(float DamageCount);
	UFUNCTION() void Die();
	
	FOnPlayerDeath PlayerDeath;

	UPROPERTY() AGun* AttachedGun;
	FVector InitialPosition;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
	class UCapsuleComponent* TriggerCapsule;
	UFUNCTION() void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
};

USTRUCT() struct FCharacterDefaultWalkSpeeds {
	GENERATED_BODY()
	UPROPERTY() AUConceptDemoPaperCharacter* Character;
	float DefaultWalkSpeed;
};