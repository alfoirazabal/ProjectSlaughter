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
class CONCEPTDEMO_API UBlooHealthHUD final : public UUserWidget
{
	GENERATED_BODY()

private:
	static void SetLifeAvailable(UImage* Image, bool bIsAvailable);

public:
	UPROPERTY(meta = (BindWidget)) UProgressBar* ProgressBar_0;
	UPROPERTY(meta = (BindWidget)) UProgressBar* GunBulletsProgressBar;
	UPROPERTY(meta = (BindWidget)) UImage* ImgHearth1;
	UPROPERTY(meta = (BindWidget)) UImage* ImgHearth2;
	UPROPERTY(meta = (BindWidget)) UImage* ImgHearth3;

protected:
	virtual void NativeOnInitialized() override;

public:
	UFUNCTION() void SetHealth(float Health) const;
	UFUNCTION() void SetLives(uint8 Lives) const;
	UFUNCTION() void SetShotsLeft(const int32 ShotsTotal, const int32 ShotsLeft);
	UFUNCTION() void SetNoGun();

	void UpdateHealth(float LifeLeft, uint8 LivesLeft) const;

};
