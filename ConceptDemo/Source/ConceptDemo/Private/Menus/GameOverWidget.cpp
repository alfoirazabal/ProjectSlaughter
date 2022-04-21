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
			}
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
	}
	this->ButtonContinue->OnClicked.AddDynamic(this, &UGameOverWidget::ContinueToMainMenu);
}

void UGameOverWidget::ContinueToMainMenu()
{
	UGameplayStatics::OpenLevel(this, "MainMenu");
}
