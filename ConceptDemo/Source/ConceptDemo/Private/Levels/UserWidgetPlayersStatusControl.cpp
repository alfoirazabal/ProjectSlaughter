// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/UserWidgetPlayersStatusControl.h"

UUserWidgetPlayersStatusControl::UUserWidgetPlayersStatusControl()
{
	this->GunAttachedStaminaBarColor = FColor(0, 0, 255, 255);
	this->NoGunAttachedStaminaBarColor = FColor(0, 255, 0, 255);
}

UUserWidgetPlayersStatusControl::~UUserWidgetPlayersStatusControl()
{
}

void UUserWidgetPlayersStatusControl::SetHealth(const float Health) const
{
	this->PbrHealth->SetPercent(Health);
}

void UUserWidgetPlayersStatusControl::SetLives(const uint8 Lives) const
{
	TArray<UImage*> HeartImages;
	HeartImages.Add(this->ImgHeart1);
	HeartImages.Add(this->ImgHeart2);
	HeartImages.Add(this->ImgHeart3);
	if (Lives <= HeartImages.Num())
	{
		for (uint8 i = 0 ; i < HeartImages.Num() ; i++)
		{
			if (i + 1 <= Lives)
			{
				HeartImages[i]->SetColorAndOpacity(FLinearColor(1, 1, 1, 1));
			}
			else
			{
				HeartImages[i]->SetColorAndOpacity(FLinearColor(0, 0, 0, 1));
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(195766230, 2, FColor::Red, "Need more hearths on the widget!");
	}
}

void UUserWidgetPlayersStatusControl::SetStaminaBar(const uint16 Total, const uint16 Current) const
{
	if (Total != 0)
	{
		const float ShotsPercent = static_cast<float>(Current) / static_cast<float>(Total);
		this->PbrStamina->SetPercent(ShotsPercent);
	}
	else
	{
		this->PbrStamina->SetPercent(1);
	}
}

void UUserWidgetPlayersStatusControl::SetGunAttached(const bool GunAttached) const
{
	if (GunAttached)
	{
		this->PbrStamina->SetFillColorAndOpacity(this->GunAttachedStaminaBarColor);
	}
	else
	{
		this->PbrStamina->SetFillColorAndOpacity(this->NoGunAttachedStaminaBarColor);
	}
}
