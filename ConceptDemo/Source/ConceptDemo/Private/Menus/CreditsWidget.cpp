// Fill out your copyright notice in the Description page of Project Settings.


#include "Menus/CreditsWidget.h"

#include "Kismet/GameplayStatics.h"

void UCreditsWidget::NativeConstruct()
{
	if (this->BackgroundTextureSequenceFlipTime <= 0)
	{
		GEngine->AddOnScreenDebugMessage(872231886, 4, FColor::Red, "Need to setup Widget Background Texture Sequence Flip Time > 0 on the editor.");
	}
	else
	{
		this->GetWorld()->GetTimerManager().SetTimer(
			this->BackgroundImageFlippingTimer, this, &UCreditsWidget::SetBackgroundImageFlipping,
			this->BackgroundTextureSequenceFlipTime, true
		);
	}
	this->ButtonGoBack->OnClicked.AddDynamic(this, &UCreditsWidget::GoBack);
}

void UCreditsWidget::NativeDestruct()
{
	this->GetWorld()->GetTimerManager().ClearTimer(this->BackgroundImageFlippingTimer);
	Super::NativeDestruct();
}

void UCreditsWidget::GoBack()
{
	UGameplayStatics::PlaySound2D(this->GetWorld(), this->GoBackSound);
	this->GetWorld()->GetTimerManager().ClearTimer(this->BackgroundImageFlippingTimer);
	UUserWidget* MainMenuWidget = CreateWidget<UUserWidget>(this->GetWorld(), this->BackWidget);
	MainMenuWidget->AddToViewport();
}

void UCreditsWidget::SetBackgroundImageFlipping()
{
	if (this->BackgroundTextureSequence.Num() > 0)
	{
		this->CurrentFlippingImageIndex++;
		if (this->CurrentFlippingImageIndex > this->BackgroundTextureSequence.Num() - 1)
		{
			this->CurrentFlippingImageIndex = 0;
		}
		this->BackgroundImage->SetBrushFromTexture(this->BackgroundTextureSequence[this->CurrentFlippingImageIndex]);
	}
}
