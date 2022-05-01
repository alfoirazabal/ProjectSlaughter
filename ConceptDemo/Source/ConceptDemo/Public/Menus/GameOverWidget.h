// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class CONCEPTDEMO_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere) TArray<UTexture2D*> BackgroundTextureSequence;
	UPROPERTY(EditAnywhere) float BackgroundTextureSequenceFlipTime;

	UPROPERTY(meta = (BindWidget)) UImage* BackgroundImage;
	UPROPERTY(meta = (BindWidget)) UImage* WinnerPlayerImage;
	UPROPERTY(meta = (BindWidget)) UTextBlock* TextBlockWinnerPlayerName;
	UPROPERTY(meta = (BindWidget)) UButton* ButtonContinue;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION() void ContinueToMainMenu();

protected:
	UPROPERTY() int CurrentFlippingImageIndex;
	UPROPERTY() FTimerHandle BackgroundImageFlippingTimer; 
	UFUNCTION() void SetBackgroundImageFlipping();
};
