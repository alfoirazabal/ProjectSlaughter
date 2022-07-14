// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class CONCEPTDEMO_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) FText VersionText = FText::FromString("V 2022.07.12-3");
	
	UPROPERTY(EditAnywhere) float BackgroundFlipTime = 0.1;
	UPROPERTY(EditAnywhere) TArray<UTexture2D*> BackgroundTextures;
	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> PlayersSelectionWidgetClass;
	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> CreditsWidgetClass;
	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> HowToPlayWidgetClass;

	
	UPROPERTY(meta = (BindWidget)) UTextBlock* TxtVersionText;
	UPROPERTY(meta = (BindWidget)) UImage* BackgroundImage;
	
	UPROPERTY(meta = (BindWidget)) UButton* ButtonPlayDemo;
	UPROPERTY(meta = (BindWidget)) UButton* ButtonExit;
	UPROPERTY(meta = (BindWidget)) UButton* ButtonCredits;
	UPROPERTY(meta = (BindWidget)) UButton* ButtonHowToPlay;

	UFUNCTION() virtual void NativeConstruct() override;

protected:
	UPROPERTY() FTimerHandle FlipBackgroundTimerHandler;
	UPROPERTY() uint16 CurrentBackgroundTextureIndex = 0;
	UFUNCTION() void FlipBackgroundImage();

	UFUNCTION() void ClickedPlayDemo();
	UFUNCTION() void ClickedCredits();
	UFUNCTION() void ClickedHowToPlay();
	UFUNCTION() void ClickedExit();
	
};
