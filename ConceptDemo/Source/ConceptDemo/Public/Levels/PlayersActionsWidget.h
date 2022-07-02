// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "PlayersActionsWidget.generated.h"


UENUM()
enum EPlayersActionsWidgetAction
{
	DropGun,
	FireGun,
	UsePower
};

UENUM()
enum EPlayersActionsWidgetControllerType
{
	KeyboardPlayer1,
	KeyboardPlayer2,
	XBoxController
};

UCLASS()
class CONCEPTDEMO_API UPlayersActionsWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;
	
	UFUNCTION() void SetActionImageEnabled(UImage* Image, bool IsEnabled);
	UFUNCTION() void MapKeyboardTypesToTextureKeys(EPlayersActionsWidgetControllerType ControllerType, TArray<UTexture2D*>& TextureKeys) const;
	
public:

    UPROPERTY(EditAnywhere, Category="Key textures") UTexture2D* TextureKeyP1KeyboardFire;
    UPROPERTY(EditAnywhere, Category="Key textures") UTexture2D* TextureKeyP1KeyboardDropWeapon;
	UPROPERTY(EditAnywhere, Category="Key textures") UTexture2D* TextureKeyP1KeyboardUsePower;
	UPROPERTY(EditAnywhere, Category="Key textures") UTexture2D* TextureKeyP2KeyboardFire;
	UPROPERTY(EditAnywhere, Category="Key textures") UTexture2D* TextureKeyP2KeyboardDropWeapon;
	UPROPERTY(EditAnywhere, Category="Key textures") UTexture2D* TextureKeyP2KeyboardUsePower;
	UPROPERTY(EditAnywhere, Category="Key textures") UTexture2D* TextureKeyControllerFire;
	UPROPERTY(EditAnywhere, Category="Key textures") UTexture2D* TextureKeyControllerDropWeapon;
	UPROPERTY(EditAnywhere, Category="Key textures") UTexture2D* TextureKeyControllerUsePower;

	UPROPERTY(EditAnywhere) float KeyDisabledOpacityLevel = 0.25;

	UPROPERTY(meta = (BindWidget)) UImage* ImgP1DropGun;
	UPROPERTY(meta = (BindWidget)) UImage* ImgP1FireGun;
	UPROPERTY(meta = (BindWidget)) UImage* ImgP1UsePower;
	
	UPROPERTY(meta = (BindWidget)) UImage* ImgP2DropGun;
	UPROPERTY(meta = (BindWidget)) UImage* ImgP2FireGun;
	UPROPERTY(meta = (BindWidget)) UImage* ImgP2UsePower;

	UFUNCTION() void SetPlayerControllerType(uint8 PlayerNumber, EPlayersActionsWidgetControllerType ControllerType) const;
	UFUNCTION() void UpdateHUD(uint8 PlayerNumber, EPlayersActionsWidgetAction WidgetAction, bool IsEnabled);
	
};
