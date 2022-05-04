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
	this->ButtonNext->OnClicked.AddDynamic(this, &UCreditsWidget::GoToNextWidget);
}

void UCreditsWidget::NativeDestruct()
{
	this->GetWorld()->GetTimerManager().ClearTimer(this->BackgroundImageFlippingTimer);
	Super::NativeDestruct();
}

void UCreditsWidget::GoToNextWidget()
{
	UGameplayStatics::PlaySound2D(this->GetWorld(), this->NextWidgetSound);
	this->GetWorld()->GetTimerManager().ClearTimer(this->BackgroundImageFlippingTimer);
	UUserWidget* NextWidget = CreateWidget<UUserWidget>(this->GetWorld(), this->NextWidgetClass);
	NextWidget->AddToViewport();
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
