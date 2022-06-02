// Fill out your copyright notice in the Description page of Project Settings.


#include "Menus/GameOverWidget.h"

#include "DemoGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UGameOverWidget::NativeConstruct()
{
	const UDemoGameInstance* GameInstance = Cast<UDemoGameInstance>(this->GetGameInstance());
	if (IsValid(GameInstance)) {
		TSubclassOf<AUConceptDemoPaperCharacter> SelectedPlayerType;
		switch (GameInstance->WinningPlayerNumber)
		{
			case 1:
				if (IsValid(GameInstance->SelectedPlayer1Type)) SelectedPlayerType = GameInstance->SelectedPlayer1Type;
				break;
			case 2:
				if (IsValid(GameInstance->SelectedPlayer2Type)) SelectedPlayerType = GameInstance->SelectedPlayer2Type;
				break;
			default:
				break;
		}
		if (IsValid(SelectedPlayerType)) {
			const AUConceptDemoPaperCharacter* DefaultObject = SelectedPlayerType.GetDefaultObject();
			if (IsValid(DefaultObject)) {
				UTexture2D* ObjectTexture = DefaultObject->CharacterImage;
				if (IsValid(ObjectTexture)) {
					this->WinnerPlayerImage->SetBrushFromTexture(ObjectTexture);
				}
				else
				{
					GEngine->AddOnScreenDebugMessage(129576123, 2, FColor::Red, "PaperCharacter Object texture invalid for winning player");
				}
				if (DefaultObject->WinSound)
				{
					UGameplayStatics::PlaySound2D(this->GetWorld(), DefaultObject->WinSound);
				}
				else
				{
					GEngine->AddOnScreenDebugMessage(284662666, 2, FColor::Red, "Player " + DefaultObject->GetName() + " has no Win Sound!");
				}
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(277177122, 2, FColor::Red, "Can't find SelectedPlayerType variable (Winning player)");
		}
		FText WinnerPlayerName;
		switch (GameInstance->WinningPlayerNumber)
		{
			case 1:
				WinnerPlayerName = GameInstance->Player1Name;
				break;
			case 2:
				WinnerPlayerName = GameInstance->Player2Name;
				break;
			default:
				break;
		}
		this->TextBlockWinnerPlayerName->SetText(WinnerPlayerName);
		this->GetWorld()->GetTimerManager().SetTimer(
			this->BackgroundImageFlippingTimer, this, &UGameOverWidget::SetBackgroundImageFlipping,
			this->BackgroundTextureSequenceFlipTime, true
		);
	}
	this->ButtonContinue->OnClicked.AddDynamic(this, &UGameOverWidget::ContinueToMainMenu);
}

void UGameOverWidget::NativeDestruct()
{
	this->GetWorld()->GetTimerManager().ClearTimer(this->BackgroundImageFlippingTimer);
	Super::NativeDestruct();
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
