// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "UserWidgetPlayersStatusControl.generated.h"

/**
 * 
 */
UCLASS()
class CONCEPTDEMO_API UUserWidgetPlayersStatusControl : public UObject
{
	
public:

	GENERATED_BODY()
	
	UUserWidgetPlayersStatusControl();
	virtual ~UUserWidgetPlayersStatusControl() override;

	UPROPERTY() UImage* ImgHeart1;
	UPROPERTY() UImage* ImgHeart2;
	UPROPERTY() UImage* ImgHeart3;
	UPROPERTY() UProgressBar* PbrHealth;
	UPROPERTY() UProgressBar* PbrStamina;
	
	UPROPERTY() FColor GunAttachedStaminaBarColor;
	UPROPERTY() FColor NoGunAttachedStaminaBarColor;

	UFUNCTION() void SetHealth(float Health) const;
	UFUNCTION() void SetLives(uint8 Lives) const;
	UFUNCTION() void SetStaminaBar(uint16 Total, uint16 Current) const;
	UFUNCTION() void SetGunAttached(bool GunAttached) const;
	
};
