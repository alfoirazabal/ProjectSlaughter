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

	UPROPERTY(EditAnywhere) FColor GunAttachedStaminaBarColor;
	UPROPERTY(EditAnywhere) FColor NoGunAttachedStaminaBarColor;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

public:
	UFUNCTION() void SetHealth(float Health) const;
	UFUNCTION() void SetLives(uint8 Lives) const;
	UFUNCTION() void SetStaminaBar(const int32 StaminaTotal, const int32 StaminaLeft) const;
	UFUNCTION() void SetPlayerName(FText Name) const;
	UFUNCTION() void SetGunAttached(bool GunAttached) const;

	void UpdateHealth(float LifeLeft, uint8 LivesLeft) const;
	
};
