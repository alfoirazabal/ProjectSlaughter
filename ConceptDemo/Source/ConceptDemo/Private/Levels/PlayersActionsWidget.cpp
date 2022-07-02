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
		Image->SetOpacity(0.5);
	}
}

void UPlayersActionsWidget::SetPlayerControllerType(uint8 PlayerNumber,
                                                    EPlayersActionsWidgetControllerType ControllerType)
{
	// TODO apply images accordingly
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
