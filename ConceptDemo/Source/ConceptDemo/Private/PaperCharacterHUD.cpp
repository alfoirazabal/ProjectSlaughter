// Fill out your copyright notice in the Description page of Project Settings.


#include "PaperCharacterHUD.h"

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

void UPaperCharacterHUD::SetShotsLeft(const int32 ShotsTotal, const int32 ShotsLeft) const
{
	const float ShotsPercent = static_cast<float>(ShotsLeft) / static_cast<float>(ShotsTotal);
	this->ProgressBarCurrentStamina->SetPercent(ShotsPercent);
}

void UPaperCharacterHUD::SetNoGun() const
{
	this->ProgressBarCurrentStamina->SetPercent(0);
}

void UPaperCharacterHUD::SetPlayerName(const FText Name) const
{
	this->TextBlockPlayerName->SetText(Name);
}

void UPaperCharacterHUD::UpdateHealth(const float LifeLeft, const uint8 LivesLeft) const
{
	this->SetHealth(LifeLeft);
	this->SetLives(LivesLeft);
}
