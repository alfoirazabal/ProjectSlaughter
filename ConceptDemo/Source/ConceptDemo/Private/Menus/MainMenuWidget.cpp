// Fill out your copyright notice in the Description page of Project Settings.


#include "Menus/MainMenuWidget.h"

#include "Kismet/KismetSystemLibrary.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	this->TxtVersionText->SetText(this->VersionText);

	this->ButtonPlayDemo->OnClicked.AddDynamic(this, &UMainMenuWidget::ClickedPlayDemo);
	this->ButtonCredits->OnClicked.AddDynamic(this, &UMainMenuWidget::ClickedCredits);
	this->ButtonHowToPlay->OnClicked.AddDynamic(this, &UMainMenuWidget::ClickedHowToPlay);
	this->ButtonExit->OnClicked.AddDynamic(this, &UMainMenuWidget::ClickedExit);
	
	this->GetWorld()->GetTimerManager().SetTimer(this->FlipBackgroundTimerHandler, this, &UMainMenuWidget::FlipBackgroundImage, this->BackgroundFlipTime, true);
}

void UMainMenuWidget::FlipBackgroundImage()
{
	if (this->BackgroundTextures.Num() > 0)
	{
		if (this->CurrentBackgroundTextureIndex > this->BackgroundTextures.Num() - 1)
		{
			this->CurrentBackgroundTextureIndex = 0;
		}
		this->BackgroundImage->SetBrushFromTexture(this->BackgroundTextures[this->CurrentBackgroundTextureIndex]);
		this->CurrentBackgroundTextureIndex++;
	}
}

void UMainMenuWidget::ClickedPlayDemo()
{
	this->GetWorld()->GetTimerManager().ClearTimer(this->FlipBackgroundTimerHandler);
	UUserWidget* PlayersSelectionWidget = CreateWidget<UUserWidget>(this->GetWorld(), this->PlayersSelectionWidgetClass);
	PlayersSelectionWidget->AddToViewport();
	this->RemoveFromViewport();
}

void UMainMenuWidget::ClickedCredits()
{
	this->GetWorld()->GetTimerManager().ClearTimer(this->FlipBackgroundTimerHandler);
	UUserWidget* CreditsWidget = CreateWidget<UUserWidget>(this->GetWorld(), this->CreditsWidgetClass);
	CreditsWidget->AddToViewport();
	this->RemoveFromViewport();
}

void UMainMenuWidget::ClickedHowToPlay()
{
	this->GetWorld()->GetTimerManager().ClearTimer(this->FlipBackgroundTimerHandler);
	UUserWidget* HowToPlayWidget = CreateWidget<UUserWidget>(this->GetWorld(), this->HowToPlayWidgetClass);
	HowToPlayWidget->AddToViewport();
	this->RemoveFromViewport();
}

void UMainMenuWidget::ClickedExit()
{
	UKismetSystemLibrary::QuitGame(this->GetWorld(), this->GetOwningPlayer(), EQuitPreference::Quit, false);
}
