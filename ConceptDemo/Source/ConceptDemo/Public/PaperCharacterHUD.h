// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "PaperCharacterHUD.generated.h"

/**
 * 
 */
UCLASS()
class CONCEPTDEMO_API UPaperCharacterHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY() TArray<UImage*> LifeHearts;
	UPROPERTY(meta = (BindWidget)) UImage* ImgHeart1;
	UPROPERTY(meta = (BindWidget)) UImage* ImgHeart2;
	UPROPERTY(meta = (BindWidget)) UImage* ImgHeart3;
	UPROPERTY(meta = (BindWidget)) UTextBlock* TextBlockPlayerName;
	UPROPERTY(meta = (BindWidget)) UProgressBar* ProgressBarCurrentLifeSize;
	UPROPERTY(meta = (BindWidget)) UProgressBar* ProgressBarCurrentStamina;

protected:
	virtual void NativeOnInitialized() override;

public:
	UFUNCTION() void SetHealth(float Health) const;
	UFUNCTION() void SetLives(uint8 Lives) const;
	UFUNCTION() void SetShotsLeft(const int32 ShotsTotal, const int32 ShotsLeft);
	UFUNCTION() void SetNoGun();

	void UpdateHealth(float LifeLeft, uint8 LivesLeft) const;
	
};
