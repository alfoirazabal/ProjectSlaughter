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
		if (Image == this->ImgP1UsePower)
		{
			this->GetWorld()->GetTimerManager().SetTimer(this->TimerHandlerP1PowerReadyIndicatorFlash, this, &UPlayersActionsWidget::FlashP1PowerUpReadyIndicator, this->PowerReadyIndicatorFlashTime, true);
		}
		else if (Image == this->ImgP2UsePower)
		{
			this->GetWorld()->GetTimerManager().SetTimer(this->TimerHandlerP2PowerReadyIndicatorFlash, this, &UPlayersActionsWidget::FlashP2PowerUpReadyIndicator, this->PowerReadyIndicatorFlashTime, true);
		}
	}
	else
	{
		Image->SetOpacity(this->KeyDisabledOpacityLevel);
		if (Image == this->ImgP1UsePower)
		{
			this->GetWorld()->GetTimerManager().ClearTimer(this->TimerHandlerP1PowerReadyIndicatorFlash);
			this->ImgP1PowerReadyIndicator->SetVisibility(ESlateVisibility::Hidden);
		}
		else if (Image == this->ImgP2UsePower)
		{
			this->GetWorld()->GetTimerManager().ClearTimer(this->TimerHandlerP2PowerReadyIndicatorFlash);
			this->ImgP2PowerReadyIndicator->SetVisibility(ESlateVisibility::Hidden);
		}
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

void UPlayersActionsWidget::FlashP1PowerUpReadyIndicator()
{
	if (this->ImgP1PowerReadyIndicator->Visibility == ESlateVisibility::Visible)
	{
		this->ImgP1PowerReadyIndicator->SetVisibility(ESlateVisibility::Hidden);
	}
	else if (this->ImgP1PowerReadyIndicator->Visibility == ESlateVisibility::Hidden)
	{
		this->ImgP1PowerReadyIndicator->SetVisibility(ESlateVisibility::Visible);
	}
}

void UPlayersActionsWidget::FlashP2PowerUpReadyIndicator()
{
	if (this->ImgP2PowerReadyIndicator->Visibility == ESlateVisibility::Visible)
	{
		this->ImgP2PowerReadyIndicator->SetVisibility(ESlateVisibility::Hidden);
	}
	else if (this->ImgP2PowerReadyIndicator->Visibility == ESlateVisibility::Hidden)
	{
		this->ImgP2PowerReadyIndicator->SetVisibility(ESlateVisibility::Visible);
	}
}

void UPlayersActionsWidget::SetPlayerPowerUpTexture(const uint8 PlayerNumber, UTexture2D* PowerUpTexture) const
{
	if (PlayerNumber == 1) this->ImgP1PowerReadyIndicator->SetBrushFromTexture(PowerUpTexture);
	else if (PlayerNumber == 2) this->ImgP2PowerReadyIndicator->SetBrushFromTexture(PowerUpTexture);
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
