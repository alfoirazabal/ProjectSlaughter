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
	UPROPERTY(EditAnywhere) AUConceptDemoPaperCharacter* Player1;
	UPROPERTY(EditAnywhere) AUConceptDemoPaperCharacter* Player2;
	UFUNCTION(BlueprintCallable) void SetupInputs();

protected:
	void P1HorizontalMovement(float AxisValue);
	void P1JumpPressed();
	void P1JumpReleased();
	void P1DropDownPressed();
	void P1Fire();
	void P1DropGun();

	void P2HorizontalMovement(float AxisValue);
	void P2JumpPressed();
	void P2JumpReleased();
	void P2DropDownPressed();
	void P2Fire();
	void P2DropGun();
	
	UFUNCTION() void P1ReactToDeath();
	UFUNCTION() void P2ReactToDeath();
	UFUNCTION() void ExitLevel();
};
