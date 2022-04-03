// Fill out your copyright notice in the Description page of Project Settings.

// Help source https://www.youtube.com/watch?v=6LzoJypuUgI

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BlooHealthHUD.generated.h"

class UProgressBar;
class UImage;

/**
 * 
 */
UCLASS()
class CONCEPTDEMO_API UBlooHealthHUD : public UUserWidget
{
	GENERATED_BODY()

private:
	void SetLifeAvailable(UImage* image, bool isAvailable);

public:
	UPROPERTY(meta = (BindWidget)) UProgressBar* ProgressBar_0;
	UPROPERTY(meta = (BindWidget)) UImage* ImgHearth1;
	UPROPERTY(meta = (BindWidget)) UImage* ImgHearth2;
	UPROPERTY(meta = (BindWidget)) UImage* ImgHearth3;

protected:
	void NativeOnInitialized() override;

public:
	UFUNCTION() void SetHealth(float health);
	UFUNCTION() void SetLives(uint8 lives);

	void UpdateHealth(float lifeLeft, uint8 livesLeft);

};
