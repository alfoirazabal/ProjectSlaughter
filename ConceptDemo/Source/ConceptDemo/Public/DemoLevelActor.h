// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConceptDemoPaperCharacter.h"
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
	
	UPROPERTY(EditAnywhere) TArray<TSubclassOf<AUConceptDemoPaperCharacter>> Characters;
	UPROPERTY(EditAnywhere) TArray<FVector> RandomPlayerSpawnLocations;
	UPROPERTY(EditAnywhere) TArray<TSubclassOf<AGun>> Guns;
	UPROPERTY(EditAnywhere) TArray<FVector> RandomGunSpawnLocations;
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

	UFUNCTION() void SpawnPlayers();
	UFUNCTION() void SpawnGuns();
	UFUNCTION() void P1ReactToDeath();
	UFUNCTION() void P2ReactToDeath();
	UFUNCTION() void ExitLevel();
};
