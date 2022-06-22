// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "UserWidgetPlayersStatus.generated.h"

/**
 * 
 */
UCLASS()
class CONCEPTDEMO_API UUserWidgetPlayersStatus : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget)) UTextBlock* TxtP1Name;
	UPROPERTY(meta = (BindWidget)) UTextBlock* TxtP2Name;
	UPROPERTY(meta = (BindWidget)) UImage* ImgP1Heart1;
	UPROPERTY(meta = (BindWidget)) UImage* ImgP1Heart2;
	UPROPERTY(meta = (BindWidget)) UImage* ImgP1Heart3;
	UPROPERTY(meta = (BindWidget)) UImage* ImgP2Heart1;
	UPROPERTY(meta = (BindWidget)) UImage* ImgP2Heart2;
	UPROPERTY(meta = (BindWidget)) UImage* ImgP2Heart3;
	UPROPERTY(meta = (BindWidget)) UProgressBar* PbrP1Life;
	UPROPERTY(meta = (BindWidget)) UProgressBar* PbrP1Stamina;
	UPROPERTY(meta = (BindWidget)) UProgressBar* PbrP2Life;
	UPROPERTY(meta = (BindWidget)) UProgressBar* PbrP2Stamina;
	UPROPERTY(meta = (BindWidget)) UImage* ImgP1CharacterType;
	UPROPERTY(meta = (BindWidget)) UImage* ImgP2CharacterType;
	UPROPERTY(meta = (BindWidget)) UTextBlock* TxtP1Score;
	UPROPERTY(meta = (BindWidget)) UTextBlock* TxtP2Score;

	UFUNCTION() virtual void NativeConstruct() override;
	
};
