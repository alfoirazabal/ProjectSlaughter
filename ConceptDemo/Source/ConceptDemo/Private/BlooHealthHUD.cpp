// Fill out your copyright notice in the Description page of Project Settings.


#include "BlooHealthHUD.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"

void UBlooHealthHUD::SetLifeAvailable(UImage* img, bool isAvailable)
{
	if (isAvailable) {
		img->SetColorAndOpacity(FLinearColor(1, 1, 1, 1));
	}
	else {
		img->SetColorAndOpacity(FLinearColor(0, 0, 0, 1));
	}
}

void UBlooHealthHUD::SetHealth(float health) 
{
	this->ProgressBar_0->SetPercent(health);
}

void UBlooHealthHUD::SetLives(uint8 lives)
{
	switch (lives)
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
	}
}

void UBlooHealthHUD::UpdateHealth(float lifeLeft, uint8 livesLeft) 
{
	this->SetHealth(lifeLeft);
	this->SetLives(livesLeft);
}

void UBlooHealthHUD::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}