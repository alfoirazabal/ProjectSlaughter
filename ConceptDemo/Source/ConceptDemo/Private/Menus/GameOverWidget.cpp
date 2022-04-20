// Fill out your copyright notice in the Description page of Project Settings.


#include "Menus/GameOverWidget.h"

#include "DemoGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UGameOverWidget::NativeConstruct()
{
	const UDemoGameInstance* GameInstance = Cast<UDemoGameInstance>(this->GetGameInstance());
	switch (GameInstance->WinningPlayerNumber)
	{
		case 1:
			this->WinnerPlayerImage->SetBrushFromTexture(GameInstance->SelectedPlayer1Type.GetDefaultObject()->CharacterImage);
			break;
		case 2:
			this->WinnerPlayerImage->SetBrushFromTexture(GameInstance->SelectedPlayer2Type.GetDefaultObject()->CharacterImage);
			break;
		default:
			break;
	}
	this->TextBlockWinnerPlayerNumber->SetText(FText::FromString(FString::FromInt(GameInstance->WinningPlayerNumber)));
	this->ButtonContinue->OnClicked.AddDynamic(this, &UGameOverWidget::ContinueToMainMenu);
}

void UGameOverWidget::ContinueToMainMenu()
{
	UGameplayStatics::OpenLevel(this, "MainMenu");
}
