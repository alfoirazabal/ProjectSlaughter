// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConceptDemoPaperCharacter.h"
#include "Engine/GameInstance.h"
#include "DemoGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class CONCEPTDEMO_API UDemoGameInstance final : public UGameInstance
{
	GENERATED_BODY()

public:

	UDemoGameInstance();
	
	UPROPERTY() TSubclassOf<AUConceptDemoPaperCharacter> SelectedPlayer1Type;
	UPROPERTY() TSubclassOf<AUConceptDemoPaperCharacter> SelectedPlayer2Type;
	UPROPERTY() FText Player1Name;
	UPROPERTY() FText Player2Name;
	UPROPERTY() uint8 WinningPlayerNumber;
	UPROPERTY(EditAnywhere) bool UseControllerForPlayer2;
	
};
