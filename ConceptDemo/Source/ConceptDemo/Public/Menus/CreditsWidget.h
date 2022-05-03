// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "CreditsWidget.generated.h"

/**
 * 
 */
UCLASS()
class CONCEPTDEMO_API UCreditsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere) TArray<UTexture2D*> BackgroundTextureSequence;
	UPROPERTY(EditAnywhere) float BackgroundTextureSequenceFlipTime;
	UPROPERTY(EditAnywhere) TSubclassOf<UUserWidget> BackWidget;
	UPROPERTY(EditAnywhere) USoundBase* GoBackSound;

	UPROPERTY(meta = (BindWidget)) UImage* BackgroundImage;
	UPROPERTY(meta = (BindWidget)) UButton* ButtonGoBack;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	UFUNCTION() void GoBack();
	
protected:
	UPROPERTY() int CurrentFlippingImageIndex;
	UPROPERTY() FTimerHandle BackgroundImageFlippingTimer; 
	UFUNCTION() void SetBackgroundImageFlipping();
	
};
