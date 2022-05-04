// Fill out your copyright notice in the Description page of Project Settings.


#include "PaperCharacterHUD.h"

void UPaperCharacterHUD::NativeConstruct()
{
	this->GunAttachedStaminaBarColor = FColor(0, 0, 255, 255);
	this->NoGunAttachedStaminaBarColor = FColor(0, 255, 0, 255);
	Super::NativeConstruct();
}

void UPaperCharacterHUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	this->LifeHearts.Reserve(3);
	this->LifeHearts.Add(this->ImgHeart1);
	this->LifeHearts.Add(this->ImgHeart2);
	this->LifeHearts.Add(this->ImgHeart3);
}

void UPaperCharacterHUD::SetHealth(const float Health) const
{
	this->ProgressBarCurrentLifeSize->SetPercent(Health);
}

void UPaperCharacterHUD::SetLives(const uint8 Lives) const
{
	if (Lives <= this->LifeHearts.Num())
	{
		for (uint8 i = 0 ; i < this->LifeHearts.Num() ; i++)
		{
			if (i + 1 <= Lives)
			{
				this->LifeHearts[i]->SetColorAndOpacity(FLinearColor(1, 1, 1, 1));
			}
			else
			{
				this->LifeHearts[i]->SetColorAndOpacity(FLinearColor(0, 0, 0, 1));
			}
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(195766230, 2, FColor::Red, "Need more hearths on the widget!");
	}
}

void UPaperCharacterHUD::SetStaminaBar(const int32 ShotsTotal, const int32 ShotsLeft) const
{
	if (ShotsTotal != 0)
	{
		const float ShotsPercent = static_cast<float>(ShotsLeft) / static_cast<float>(ShotsTotal);
		this->ProgressBarCurrentStamina->SetPercent(ShotsPercent);
	}
	else
	{
		this->ProgressBarCurrentStamina->SetPercent(1);
	}
}

void UPaperCharacterHUD::SetPlayerName(const FText Name) const
{
	this->TextBlockPlayerName->SetText(Name);
}

void UPaperCharacterHUD::SetGunAttached(const bool GunAttached) const
{
	if (GunAttached)
	{
		this->ProgressBarCurrentStamina->SetFillColorAndOpacity(this->GunAttachedStaminaBarColor);
	}
	else
	{
		this->ProgressBarCurrentStamina->SetFillColorAndOpacity(this->NoGunAttachedStaminaBarColor);
	}
}

void UPaperCharacterHUD::UpdateHealth(const float LifeLeft, const uint8 LivesLeft) const
{
	this->SetHealth(LifeLeft);
	this->SetLives(LivesLeft);
}
