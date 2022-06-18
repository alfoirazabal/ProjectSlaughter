// Fill out your copyright notice in the Description page of Project Settings.


#include "Menus/GameOverWidget.h"
#include "Kismet/GameplayStatics.h"

void UGameOverWidget::NativeConstruct()
{
	this->DemoGameInstance = Cast<UDemoGameInstance>(this->GetGameInstance());
	if (IsValid(this->DemoGameInstance)) {
		this->GetWorld()->GetTimerManager().SetTimer(
			this->BackgroundImageFlippingTimer, this, &UGameOverWidget::SetBackgroundImageFlipping,
			this->BackgroundTextureSequenceFlipTime, true
		);
		this->FillSurvivalWinner();
		this->FillScores();
	}
	this->ButtonContinue->OnClicked.AddDynamic(this, &UGameOverWidget::ContinueToMainMenu);
}

void UGameOverWidget::NativeDestruct()
{
	this->GetWorld()->GetTimerManager().ClearTimer(this->BackgroundImageFlippingTimer);
	Super::NativeDestruct();
}

void UGameOverWidget::FillSurvivalWinner()
{
	TSubclassOf<AConceptDemoPaperCharacter> SelectedPlayerType;
	switch (this->DemoGameInstance->WinnerSurvivorPlayerNumber)
	{
	case 1:
		if (IsValid(this->DemoGameInstance->SelectedPlayer1Type)) SelectedPlayerType = this->DemoGameInstance->SelectedPlayer1Type;
		break;
	case 2:
		if (IsValid(this->DemoGameInstance->SelectedPlayer2Type)) SelectedPlayerType = this->DemoGameInstance->SelectedPlayer2Type;
		break;
	default:
		break;
	}
	if (IsValid(SelectedPlayerType)) {
		const AConceptDemoPaperCharacter* DefaultObject = SelectedPlayerType.GetDefaultObject();
		if (IsValid(DefaultObject)) {
			UTexture2D* ObjectTexture = DefaultObject->CharacterFaceImage;
			if (IsValid(ObjectTexture)) {
				this->ImgWinnerSurviving->SetBrushFromTexture(ObjectTexture);
			}
			if (DefaultObject->WinSound)
			{
				UGameplayStatics::PlaySound2D(this->GetWorld(), DefaultObject->WinSound);
			}
		}
	}
	FText WinnerPlayerName;
	switch (this->DemoGameInstance->WinnerSurvivorPlayerNumber)
	{
	case 1:
		WinnerPlayerName = this->DemoGameInstance->Player1Name;
		break;
	case 2:
		WinnerPlayerName = this->DemoGameInstance->Player2Name;
		break;
	default:
		break;
	}
	this->TxtWinnerSurvivingName->SetText(WinnerPlayerName);
}

void UGameOverWidget::FillScores()
{
	FNumberFormattingOptions NumberFormattingOptions;
	NumberFormattingOptions.MinimumFractionalDigits = 2;
	NumberFormattingOptions.MaximumFractionalDigits = 2;
	AConceptDemoPaperCharacter* Character1;
	AConceptDemoPaperCharacter* Character2;
	if (this->DemoGameInstance->Player1Score >= this->DemoGameInstance->Player2Score)
	{
		Character1 = this->DemoGameInstance->SelectedPlayer1Type.GetDefaultObject();
		Character2 = this->DemoGameInstance->SelectedPlayer2Type.GetDefaultObject();
		this->TxtFirstPlayerName->SetText(this->DemoGameInstance->Player1Name);
		this->TxtSecondPlayerName->SetText(this->DemoGameInstance->Player2Name);
		this->TxtFirstPlayerScore->SetText(FText::AsNumber(this->DemoGameInstance->Player1Score, &NumberFormattingOptions));
		this->TxtSecondPlayerScore->SetText(FText::AsNumber(this->DemoGameInstance->Player2Score, &NumberFormattingOptions));
	}
	else
	{
		Character1 = this->DemoGameInstance->SelectedPlayer2Type.GetDefaultObject();
		Character2 = this->DemoGameInstance->SelectedPlayer1Type.GetDefaultObject();
		this->TxtFirstPlayerName->SetText(this->DemoGameInstance->Player2Name);
		this->TxtSecondPlayerName->SetText(this->DemoGameInstance->Player1Name);
		this->TxtFirstPlayerScore->SetText(FText::AsNumber(this->DemoGameInstance->Player2Score, &NumberFormattingOptions));
		this->TxtSecondPlayerScore->SetText(FText::AsNumber(this->DemoGameInstance->Player1Score, &NumberFormattingOptions));
	}
	this->ImgWinnerScore1->SetBrushFromTexture(Character1->CharacterFaceImage);
	this->ImgWinnerScore2->SetBrushFromTexture(Character2->CharacterFaceImage);
}


void UGameOverWidget::ContinueToMainMenu()
{
	UGameplayStatics::OpenLevel(this, "MainMenu");
}

void UGameOverWidget::SetBackgroundImageFlipping()
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
