// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class CONCEPTDEMO_API AMainMenuGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	AMainMenuGameModeBase();

	UPROPERTY() UAudioComponent* BackgroundAudioComponent;
	UPROPERTY(BlueprintReadWrite) bool ReplayIfSameAudioIsRequested;

	UFUNCTION(BlueprintCallable) void PlayBackgroundAudio(USoundBase* Sound) const;
	UFUNCTION(BlueprintCallable) void StopBackgroundAudio() const;
	
};
