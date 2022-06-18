// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemoGameInstance.h"
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
	UPROPERTY(meta = (BindWidget)) UImage* ImgWinnerSurviving;
	UPROPERTY(meta = (BindWidget)) UTextBlock* TxtWinnerSurvivingName;
	UPROPERTY(meta = (BindWidget)) UButton* ButtonContinue;

	UPROPERTY(meta = (BindWidget)) UImage* ImgWinnerScore1;
	UPROPERTY(meta = (BindWidget)) UImage* ImgWinnerScore2;
	UPROPERTY(meta = (BindWidget)) UTextBlock* TxtFirstPlayerName;
	UPROPERTY(meta = (BindWidget)) UTextBlock* TxtSecondPlayerName;
	UPROPERTY(meta = (BindWidget)) UTextBlock* TxtFirstPlayerScore;
	UPROPERTY(meta = (BindWidget)) UTextBlock* TxtSecondPlayerScore;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY() UDemoGameInstance* DemoGameInstance;
	UFUNCTION() void FillSurvivalWinner();
	UFUNCTION() void FillScores();
	UFUNCTION() void ContinueToMainMenu();

protected:
	UPROPERTY() int CurrentFlippingImageIndex;
	UPROPERTY() FTimerHandle BackgroundImageFlippingTimer; 
	UFUNCTION() void SetBackgroundImageFlipping();
};
