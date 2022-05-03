// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Components/AudioComponent.h>

#include "CoreMinimal.h"
#include "ConceptDemoPaperCharacter.h"
#include "DemoGameInstance.h"
#include "Engine/LevelScriptActor.h"
#include "Guns/SpawnerGun.h"
#include "DemoLevelActor.generated.h"

/**
 * 
 */
UCLASS()
class CONCEPTDEMO_API ADemoLevelActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	
	ADemoLevelActor();

	UPROPERTY() UDemoGameInstance* GameInstance;
	UPROPERTY(EditAnywhere, Category = "Players") TArray<FVector> RandomPlayerSpawnLocations;
	UPROPERTY(EditAnywhere, Category = "Guns") TArray<TSubclassOf<AGun>> Guns;
	UPROPERTY(EditAnywhere, Category = "Guns") TArray<ASpawnerGun*> SpawnerGuns;
	UPROPERTY(EditAnywhere, Category = "Guns") uint8 LevelGunsCount;
	UPROPERTY(EditAnywhere, Category = "Guns") float GunsSpawnCheckTimeInSeconds;
	UPROPERTY(EditAnywhere, Category = "Players") TSubclassOf<AUConceptDemoPaperCharacter> Player1Type;
	UPROPERTY(EditAnywhere, Category = "Players") TSubclassOf<AUConceptDemoPaperCharacter> Player2Type;
	UPROPERTY() AUConceptDemoPaperCharacter* Player1;
	UPROPERTY() AUConceptDemoPaperCharacter* Player2;
	UPROPERTY(EditAnywhere, Category = "Music") TArray<USoundBase*> LevelMusic;
	UPROPERTY(EditAnywhere, Category = "Music") UAudioComponent* LevelMusicComponent;
	UPROPERTY() int CurrentBackgroundMusicPlayingIndex;
	
	virtual void BeginPlay() override;
	
	UFUNCTION() void SetupInputs();

protected:
	void P1HorizontalMovement(float AxisValue);
	void P1JumpPressed();
	void P1JumpReleased();
	void P1DropDownPressed();
	void P1Fire(const float AxisValue);
	void P1DropGun();
	void P1UsePower();

	void P2HorizontalMovement(float AxisValue);
	void P2JumpPressed();
	void P2JumpReleased();
	void P2DropDownPressed();
	void P2Fire(const float AxisValue);
	void P2DropGun();
	void P2UsePower();

	UFUNCTION() void SpawnPlayers();
	UFUNCTION() void SpawnGuns();
	UFUNCTION() void P1ReactToDeath();
	UFUNCTION() void P2ReactToDeath();
	UFUNCTION() void ReactToGunDeath(AGun* Gun);
	UFUNCTION() void ExitLevel();
};
