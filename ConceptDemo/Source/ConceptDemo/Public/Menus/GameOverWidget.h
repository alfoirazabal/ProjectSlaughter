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
	UPROPERTY(meta = (BindWidget)) UImage* WinnerPlayerImage;
	UPROPERTY(meta = (BindWidget)) UTextBlock* TextBlockWinnerPlayerNumber;
	UPROPERTY(meta = (BindWidget)) UButton* ButtonContinue;

	virtual void NativeConstruct() override;

	UFUNCTION() void ContinueToMainMenu();
};
