// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ConceptDemoPaperCharacter.h"
#include "Engine/GameInstance.h"
#include "DemoGameInstance.generated.h"

/**
 * 
 */
UCLASS(Config=Settings)
class CONCEPTDEMO_API UDemoGameInstance final : public UGameInstance
{
	GENERATED_BODY()

public:

	UDemoGameInstance();
	
	UPROPERTY() TSubclassOf<AConceptDemoPaperCharacter> SelectedPlayer1Type;
	UPROPERTY() TSubclassOf<AConceptDemoPaperCharacter> SelectedPlayer2Type;
	UPROPERTY() FText Player1Name;
	UPROPERTY() FText Player2Name;
	UPROPERTY() uint8 WinnerSurvivorPlayerNumber;
	UPROPERTY() uint8 WinnerScorePlayerNumber;
	UPROPERTY() float Player1Score;
	UPROPERTY() float Player2Score;
	UPROPERTY(EditAnywhere, Config) bool UseControllerForPlayer2;
	
};
