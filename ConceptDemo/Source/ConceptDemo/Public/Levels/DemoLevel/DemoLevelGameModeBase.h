// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Levels/UserWidgetPlayersStatus.h"
#include "DemoLevelGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CONCEPTDEMO_API ADemoLevelGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADemoLevelGameModeBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite) UUserWidgetPlayersStatus* PlayerStatusWidget;
	
};
