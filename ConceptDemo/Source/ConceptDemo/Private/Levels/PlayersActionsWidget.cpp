// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/PlayersActionsWidget.h"

void UPlayersActionsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	this->UpdateHUD(1, UsePower, false);
	this->UpdateHUD(1, FireGun, false);
	this->UpdateHUD(1, DropGun, false);
	this->UpdateHUD(2, UsePower, false);
	this->UpdateHUD(2, FireGun, false);
	this->UpdateHUD(2, DropGun, false);
}

void UPlayersActionsWidget::SetActionImageEnabled(UImage* Image, const bool IsEnabled)
{
	if (IsEnabled)
	{
		Image->SetOpacity(1);
	}
	else
	{
		Image->SetOpacity(this->KeyDisabledOpacityLevel);
	}
}

void UPlayersActionsWidget::MapKeyboardTypesToTextureKeys(const EPlayersActionsWidgetControllerType ControllerType,
                                                          TArray<UTexture2D*>& TextureKeys) const
{
	if (ControllerType == KeyboardPlayer1)
	{
		TextureKeys.Add(this->TextureKeyP1KeyboardDropWeapon);
		TextureKeys.Add(this->TextureKeyP1KeyboardFire);
		TextureKeys.Add(this->TextureKeyP1KeyboardUsePower);
	}
	else if (ControllerType == KeyboardPlayer2)
	{
		TextureKeys.Add(this->TextureKeyP2KeyboardDropWeapon);
		TextureKeys.Add(this->TextureKeyP2KeyboardFire);
		TextureKeys.Add(this->TextureKeyP2KeyboardUsePower);
	}
	else if (ControllerType == XBoxController)
	{
		TextureKeys.Add(this->TextureKeyControllerDropWeapon);
		TextureKeys.Add(this->TextureKeyControllerFire);
		TextureKeys.Add(this->TextureKeyControllerUsePower);
	}
}

void UPlayersActionsWidget::SetPlayerControllerType(const uint8 PlayerNumber,
                                                    const EPlayersActionsWidgetControllerType ControllerType) const
{
	TArray<UImage*> Images;
	TArray<UTexture2D*> TextureKeys;
	Images.Reserve(3);
	TextureKeys.Reserve(3);
	if (PlayerNumber == 1)
	{
		Images.Add(this->ImgP1DropGun);
		Images.Add(this->ImgP1FireGun);
		Images.Add(this->ImgP1UsePower);
	}
	else if (PlayerNumber == 2)
	{
		Images.Add(this->ImgP2DropGun);
		Images.Add(this->ImgP2FireGun);
		Images.Add(this->ImgP2UsePower);
	}
	this->MapKeyboardTypesToTextureKeys(ControllerType, TextureKeys);
	for (uint8 i = 0 ; i < Images.Num() ; i++) Images[i]->SetBrushFromTexture(TextureKeys[i]);
}

void UPlayersActionsWidget::UpdateHUD(const uint8 PlayerNumber, const EPlayersActionsWidgetAction WidgetAction, const bool IsEnabled)
{
	if (PlayerNumber == 1)
	{
		switch (WidgetAction)
		{
			case DropGun:
				SetActionImageEnabled(this->ImgP1DropGun, IsEnabled);
				break;
			case FireGun:
				SetActionImageEnabled(this->ImgP1FireGun, IsEnabled);
				break;
			case UsePower:
				SetActionImageEnabled(this->ImgP1UsePower, IsEnabled);
				break;
		}
	}
	else if (PlayerNumber == 2)
	{
		switch (WidgetAction)
		{
			case DropGun:
				SetActionImageEnabled(this->ImgP2DropGun, IsEnabled);
				break;
			case FireGun:
				SetActionImageEnabled(this->ImgP2FireGun, IsEnabled);
				break;
			case UsePower:
				SetActionImageEnabled(this->ImgP2UsePower, IsEnabled);
				break;
		}
	}
}
