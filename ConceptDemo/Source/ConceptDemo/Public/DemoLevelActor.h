// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConceptDemoPaperCharacter.h"
#include "DemoGameInstance.h"
#include "Engine/LevelScriptActor.h"
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
	UPROPERTY(EditAnywhere, Category = "Guns") TArray<TSubclassOf<AGun>> RandomGuns;
	UPROPERTY(EditAnywhere, Category = "Guns") TArray<FVector> RandomGunSpawnLocations;
	UPROPERTY(EditAnywhere, Category = "SpecialGuns") TArray<TSubclassOf<AGun>> SpecialGuns;
	UPROPERTY(EditAnywhere, Category = "SpecialGuns") TArray<FVector> SpecialGunSpawnLocations;
	UPROPERTY(EditAnywhere, Category = "SpecialGuns") float SpecialGunsSpawnTime;
	UPROPERTY(EditAnywhere, Category = "Guns") float GunsSpawnCheckTimeInSeconds;
	UPROPERTY(EditAnywhere, Category = "Guns") int8 LevelGunsCount;
	UPROPERTY(EditAnywhere, Category = "Players") TSubclassOf<AUConceptDemoPaperCharacter> Player1Type;
	UPROPERTY(EditAnywhere, Category = "Players") TSubclassOf<AUConceptDemoPaperCharacter> Player2Type;
	UPROPERTY() AUConceptDemoPaperCharacter* Player1;
	UPROPERTY() AUConceptDemoPaperCharacter* Player2;

	virtual void BeginPlay() override;
	
	UFUNCTION() void SetupInputs();

protected:
	void P1HorizontalMovement(float AxisValue);
	void P1JumpPressed();
	void P1JumpReleased();
	void P1DropDownPressed();
	void P1Fire(const float AxisValue);
	void P1DropGun();

	void P2HorizontalMovement(float AxisValue);
	void P2JumpPressed();
	void P2JumpReleased();
	void P2DropDownPressed();
	void P2Fire(const float AxisValue);
	void P2DropGun();

	UPROPERTY() TArray<AGun*> LevelGuns;
	UPROPERTY() TArray<FVector> ReservedGunsSpawnLocations;

	UFUNCTION() void SpawnPlayers();
	UFUNCTION() void SpawnGuns();
	UFUNCTION() void P1ReactToDeath();
	UFUNCTION() void P2ReactToDeath();
	UFUNCTION() void ReactToGunDeath(AGun* Gun);
	UFUNCTION() void ExitLevel();
};
