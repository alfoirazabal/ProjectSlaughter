// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <PaperFlipbook.h>

#include "Guns/Gun.h"
#include "PaperCharacter.h"
#include "ConceptDemoPaperPawn.h"
#include "Characters/PowerupReadyIndicator.h"
#include "Characters/PowerupReadyProp.h"
#include "Characters/Skull.h"
#include "Helpers/DamageLevel.h"
#include "Helpers/PaperCharacterSounds.h"
#include "Levels/UserWidgetPlayersStatusControl.h"
#include "Props/Death/DeathIndicator.h"
#include "Props/Droppables/Droppable.h"
#include "ConceptDemoPaperCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerLifeLost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerGunDropped);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerGunAttached);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerPowerReady);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerPowerUsed);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CONCEPTDEMO_API AConceptDemoPaperCharacter : public AConceptDemoPaperPawn
{
	GENERATED_BODY()

	void MoveGun() const;
	void CheckCharacterFall();

public:	
	// Sets default values for this component's properties
	AConceptDemoPaperCharacter();

	UFUNCTION() void BindInputs();

	UPROPERTY(EditAnywhere) UTexture2D* CharacterImage;
	UPROPERTY(EditAnywhere) UTexture2D* CharacterFaceImage;
	UPROPERTY(EditAnywhere) FString PlayerDescription;

	UPROPERTY(EditAnywhere) TSubclassOf<APowerupReadyIndicator> PowerUpReadyIndicatorType;
	UPROPERTY(EditAnywhere) UPaperFlipbook* PowerUpReadyIndicatorFlipBook;
	UPROPERTY(EditAnywhere) FVector PowerUpReadyIndicatorRelativeLocation;
	UPROPERTY(EditAnywhere) UTexture2D* PowerUpReadyIndicatorTexture;
	UPROPERTY() APowerupReadyIndicator* CurrentPowerUpReadyIndicator;
	
	UPROPERTY() UUserWidgetPlayersStatusControl* UserWidgetPlayersStatusControl;

	UPROPERTY(EditAnywhere) FPaperCharacterSounds PaperCharacterSounds;

protected:
	// Called when the game starts
	UPROPERTY(EditAnywhere, Category="Concept Demo Action Sprites DamageLevel1") UPaperFlipbook* IdleFlipBookDamageLevel1;
	UPROPERTY(EditAnywhere, Category="Concept Demo Action Sprites DamageLevel1") UPaperFlipbook* MovingFlipBookDamageLevel1;
	UPROPERTY(EditAnywhere, Category="Concept Demo Action Sprites DamageLevel1") UPaperFlipbook* JumpingFlipBookDamageLevel1;
	UPROPERTY(EditAnywhere, Category="Concept Demo Action Sprites DamageLevel2") UPaperFlipbook* IdleFlipBookDamageLevel2;
	UPROPERTY(EditAnywhere, Category="Concept Demo Action Sprites DamageLevel2") UPaperFlipbook* MovingFlipBookDamageLevel2;
	UPROPERTY(EditAnywhere, Category="Concept Demo Action Sprites DamageLevel2") UPaperFlipbook* JumpingFlipBookDamageLevel2;
	UPROPERTY(EditAnywhere, Category="Concept Demo Action Sprites") UPaperFlipbook* CharacterDeadFlipBook;
	UPROPERTY() UPaperFlipbook* IdleFlipBook;
	UPROPERTY() UPaperFlipbook* MovingFlipBook;
	UPROPERTY() UPaperFlipbook* JumpingFlipBook;
	UPROPERTY(EditAnywhere) TEnumAsByte<EDamageLevel> DamageLevel;
	UFUNCTION() void UpdateDamageLevel();
	UPROPERTY(EditAnywhere, Category="Concept Demo Action Sprites DamageLevel2") float DamageLevel2Threshold;
	UPROPERTY(EditAnywhere, Category="Concept Demo Drops") TSubclassOf<ASkull> DeathSkull;
	UPROPERTY(EditAnywhere, Category="Character Asset Positions") FVector RelativeGunAttachLocation;
	UPROPERTY(EditAnywhere, Category="Character Asset Positions") float RelativeGunDropDistance;

	UPROPERTY(EditAnywhere, Category="Respawning") float TimeBetweenActorRespawnBlink;
	UPROPERTY(EditAnywhere, Category="Respawning") float RespawnBlinkCount;
	UPROPERTY(EditAnywhere, Category="Death") TSubclassOf<ADeathIndicator> DeathIndicatorType;
	UPROPERTY(EditAnywhere, Category="PowerUp") TSubclassOf<APowerupReadyProp> PowerUpReadyPropType;
	UPROPERTY(EditAnywhere, Category="Droppables") TArray<TSubclassOf<ADroppable>> DroppableTypes;
	UPROPERTY() uint16 CurrentHideAndShowCount;
	
	UPROPERTY(EditAnywhere) FText PlayerName;
	
	UPROPERTY() TArray<AGun*> GunsIgnored;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 Lives;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float LifeSize;

	UPROPERTY(BlueprintReadWrite) uint8 CurrentLives;
	UPROPERTY(BlueprintReadWrite) float CurrentLifeSize;
	
	UPROPERTY(EditAnywhere) uint16 SpecialPowerLoadTime;
	uint16 CurrentSpecialPowerLoadTime;
	UPROPERTY() bool SpecialPowerReadyPropShown;
	
	UPROPERTY() FTimerHandle RespawnTimer;
	
	virtual void BeginPlay() override;
	void MakeFallingDeathWithIndicator();
	void MakeFallingDeath();

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeginOverlapEvent);
	
	UFUNCTION() void UpdateHealthIndicator() const;
	UFUNCTION() void Respawn();
	UFUNCTION(BlueprintCallable) void HandleMovement(float ScaleValue);
	UFUNCTION(BlueprintCallable) void DropDown();
	virtual void Jump() override;
	UFUNCTION() void AttachGun(AGun* Gun);
	UFUNCTION(BlueprintCallable) virtual void DropGun();
	UFUNCTION() bool HasGun() const;
	UFUNCTION() bool CanUsePower() const;
	UFUNCTION(BlueprintCallable) virtual void Fire();
	UFUNCTION() void FireAxis(const float AxisValue);
	UFUNCTION() virtual void UsePower();
	UFUNCTION() void UpdateShotsCount();
	UFUNCTION() void Harm(float DamageCount);
	UFUNCTION() void AddLife(float Life);
	UFUNCTION() void ProcessRespawning();
	UFUNCTION() void Die();
	
	FOnPlayerDeath PlayerDeath;
	FOnPlayerLifeLost PlayerLifeLost;
	FOnPlayerGunAttached PlayerGunAttached;
	FOnPlayerGunDropped PlayerGunDropped;
	FOnPlayerPowerReady PlayerPowerReady;
	FOnPlayerPowerUsed PlayerPowerUsed;

	UPROPERTY() AGun* AttachedGun;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
	class UCapsuleComponent* TriggerCapsule;
	UFUNCTION() void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION() void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
};

USTRUCT() struct FCharacterDefaultWalkSpeeds {
	GENERATED_BODY()
	UPROPERTY() AConceptDemoPaperCharacter* Character;
	float DefaultWalkSpeed;
};