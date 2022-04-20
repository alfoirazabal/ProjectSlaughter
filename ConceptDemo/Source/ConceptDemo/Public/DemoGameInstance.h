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
class CONCEPTDEMO_API UDemoGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	TSubclassOf<AUConceptDemoPaperCharacter> SelectedPlayer1Type;
	TSubclassOf<AUConceptDemoPaperCharacter> SelectedPlayer2Type;
	UPROPERTY() uint8 WinningPlayerNumber;
	
};
