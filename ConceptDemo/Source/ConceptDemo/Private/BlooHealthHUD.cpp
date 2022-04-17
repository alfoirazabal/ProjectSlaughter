// Fill out your copyright notice in the Description page of Project Settings.


#include "BlooHealthHUD.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"

void UBlooHealthHUD::SetLifeAvailable(UImage* Image, const bool bIsAvailable)
{
	if (bIsAvailable) {
		Image->SetColorAndOpacity(FLinearColor(1, 1, 1, 1));
	}
	else {
		Image->SetColorAndOpacity(FLinearColor(0, 0, 0, 1));
	}
}

void UBlooHealthHUD::SetHealth(const float Health) const
{
	this->ProgressBar_0->SetPercent(Health);
}

void UBlooHealthHUD::SetLives(const uint8 Lives) const
{
	switch (Lives)
	{
		case 3:
			this->SetLifeAvailable(this->ImgHearth3, true);
			this->SetLifeAvailable(this->ImgHearth2, true);
			this->SetLifeAvailable(this->ImgHearth1, true);
			break;
		case 2:
			this->SetLifeAvailable(this->ImgHearth3, false);
			this->SetLifeAvailable(this->ImgHearth2, true);
			this->SetLifeAvailable(this->ImgHearth1, true);
			break;
		case 1:
			this->SetLifeAvailable(this->ImgHearth3, false);
			this->SetLifeAvailable(this->ImgHearth2, false);
			this->SetLifeAvailable(this->ImgHearth1, true);
			break;
		case 0:
			this->SetLifeAvailable(this->ImgHearth3, false);
			this->SetLifeAvailable(this->ImgHearth2, false);
			this->SetLifeAvailable(this->ImgHearth1, false);
			break;
		default:
			break;
	}
}

void UBlooHealthHUD::SetShotsLeft(const int32 ShotsTotal, const int32 ShotsLeft)
{
	const float ShotsPercent = static_cast<float>(ShotsLeft) / static_cast<float>(ShotsTotal);
	this->GunBulletsProgressBar->SetPercent(ShotsPercent);
}

void UBlooHealthHUD::SetNoGun()
{
	this->GunBulletsProgressBar->SetPercent(0);
}

void UBlooHealthHUD::UpdateHealth(const float LifeLeft, const uint8 LivesLeft) const
{
	this->SetHealth(LifeLeft);
	this->SetLives(LivesLeft);
}

void UBlooHealthHUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}