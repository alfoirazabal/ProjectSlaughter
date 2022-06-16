// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <PaperFlipbook.h>

#include "Guns/Gun.h"
#include "PaperCharacter.h"
#include "PaperCharacterHUD.h"
#include "UConceptDemoPaperPawn.h"
#include "Characters/PowerupReadyIndicator.h"
#include "Characters/PowerupReadyProp.h"
#include "Characters/Skull.h"
#include "Levels/UserWidgetPlayersStatusControl.h"
#include "Props/Death/DeathIndicator.h"
#include "Props/Droppables/Droppable.h"
#include "ConceptDemoPaperCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDeath);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CONCEPTDEMO_API AUConceptDemoPaperCharacter : public AUConceptDemoPaperPawn
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

	UFUNCTION() void BindInputs();

	UPROPERTY(EditAnywhere) UTexture2D* CharacterImage;
	UPROPERTY(EditAnywhere) UTexture2D* CharacterFaceImage;
	UPROPERTY(EditAnywhere) FString PlayerDescription;

	UPROPERTY(EditAnywhere) TSubclassOf<APowerupReadyIndicator> PowerUpReadyIndicatorType;
	UPROPERTY(EditAnywhere) UPaperFlipbook* PowerUpReadyIndicatorFlipBook;
	UPROPERTY(EditAnywhere) FVector PowerUpReadyIndicatorRelativeLocation;
	UPROPERTY() APowerupReadyIndicator* CurrentPowerUpReadyIndicator;
	
	UPROPERTY() UserWidgetPlayersStatusControl* UserWidgetPlayersStatusControl;

	UPROPERTY(EditAnywhere, Category="Sounds") USoundBase* JumpSound;
	UPROPERTY(EditAnywhere, Category="Sounds") USoundBase* PowerSound;
	UPROPERTY(EditAnywhere, Category="Sounds") USoundBase* DamageReceivedSound;
	UPROPERTY(EditAnywhere, Category="Sounds") USoundBase* AttachGunSound;
	UPROPERTY(EditAnywhere, Category="Sounds") USoundBase* RespawnSound;
	UPROPERTY(EditAnywhere, Category="Sounds") USoundBase* WinSound;
	UPROPERTY(EditAnywhere, Category="Sounds") USoundBase* PowerUpReadySound;

protected:
	// Called when the game starts
	UPROPERTY(EditAnywhere, Category="Concept Demo Action Sprites DamageLevel1") UPaperFlipbook* IdleFlipBookDamageLevel1;
	UPROPERTY(EditAnywhere, Category="Concept Demo Action Sprites DamageLevel1") UPaperFlipbook* MovingFlipBookDamageLevel1;
	UPROPERTY(EditAnywhere, Category="Concept Demo Action Sprites DamageLevel1") UPaperFlipbook* JumpingFlipBookDamageLevel1;
	UPROPERTY(EditAnywhere, Category="Concept Demo Action Sprites DamageLevel2") UPaperFlipbook* IdleFlipBookDamageLevel2;
	UPROPERTY(EditAnywhere, Category="Concept Demo Action Sprites DamageLevel2") UPaperFlipbook* MovingFlipBookDamageLevel2;
	UPROPERTY(EditAnywhere, Category="Concept Demo Action Sprites DamageLevel2") UPaperFlipbook* JumpingFlipBookDamageLevel2;
	UPROPERTY() UPaperFlipbook* IdleFlipBook;
	UPROPERTY() UPaperFlipbook* MovingFlipBook;
	UPROPERTY() UPaperFlipbook* JumpingFlipBook;
	UFUNCTION() void UpdateFlipBooks();
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
	
	EFacing_Direction FacingDirection;
	UPROPERTY() TArray<AGun*> GunsIgnored;

	UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 Lives;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float LifeSize;

	UPROPERTY(BlueprintReadWrite) uint8 CurrentLives;
	UPROPERTY(BlueprintReadWrite) float CurrentLifeSize;
	
	UPROPERTY(EditAnywhere) uint16 SpecialPowerLoadTime;
	uint16 CurrentSpecialPowerLoadTime;
	UPROPERTY() bool SpecialPowerReadyPropShown;
	
	UPROPERTY() bool Immune;
	UPROPERTY() FTimerHandle RespawnTimer;
	
	virtual void BeginPlay() override;
	void MakeFallingDeathWithIndicator();
	void MakeFallingDeath();

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBeginOverlapEvent);
	
	UFUNCTION() FRotator GetFacingRotation() const;
	UFUNCTION() void UpdateHealthIndicator() const;
	UFUNCTION() void Respawn();
	UFUNCTION(BlueprintCallable) void HandleMovement(float ScaleValue);
	UFUNCTION(BlueprintCallable) void DropDown();
	virtual void Jump() override;
	UFUNCTION() void AttachGun(AGun* Gun);
	UFUNCTION(BlueprintCallable) virtual void DropGun();
	UFUNCTION() bool HasGun() const;
	UFUNCTION(BlueprintCallable) virtual void Fire();
	UFUNCTION() void FireAxis(const float AxisValue);
	UFUNCTION() virtual void UsePower();
	UFUNCTION() void UpdateShotsCount();
	UFUNCTION() void TakeDamage(float DamageCount);
	UFUNCTION() void AddLife(float Life);
	UFUNCTION() void ProcessRespawning();
	UFUNCTION() void Die();
	
	FOnPlayerDeath PlayerDeath;

	UPROPERTY() AGun* AttachedGun;
	FVector InitialPosition;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//UPROPERTY(EditAnywhere, Category = "Spawn Sprite") class UPaperSprite* SpawnSprite;

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