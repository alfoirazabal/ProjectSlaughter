// Fill out your copyright notice in the Description page of Project Settings.


#include "Menus/PlayerSelectionWidget.h"

#include "PaperFlipbookComponent.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"

void UPlayerSelectionWidget::NativeConstruct()
{
	if (this->CharacterTypes.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(19576223, 2, FColor::Red, "Need to setup character types for PlayerSelectionWidget");
	}
	else
	{
		this->Player1CharacterIndex = FMath::RandRange(0, this->CharacterTypes.Num() - 1);
		this->Player2CharacterIndex = FMath::RandRange(0, this->CharacterTypes.Num() - 1);
		this->Player1Character = this->CharacterTypes[this->Player1CharacterIndex].GetDefaultObject();
		this->Player2Character = this->CharacterTypes[this->Player2CharacterIndex].GetDefaultObject();
		this->Player1ChangeButton->OnClicked.AddUniqueDynamic(this, &UPlayerSelectionWidget::ChangePlayer1);
		this->Player2ChangeButton->OnClicked.AddUniqueDynamic(this, &UPlayerSelectionWidget::ChangePlayer2);
		this->ButtonGoBack->OnClicked.AddUniqueDynamic(this, &UPlayerSelectionWidget::GoBack);
		this->ButtonBegin->OnClicked.AddUniqueDynamic(this, &UPlayerSelectionWidget::BeginGame);
		this->UpdatePlayer1();
		this->UpdatePlayer2();
	}
}

void UPlayerSelectionWidget::ChangePlayer1()
{
	if (this->Player1CharacterIndex == this->CharacterTypes.Num() - 1)
	{
		this->Player1CharacterIndex = 0;
	}
	else
	{
		this->Player1CharacterIndex++;
	}
	this->Player1Character = this->CharacterTypes[this->Player1CharacterIndex].GetDefaultObject();
	this->UpdatePlayer1();
}

void UPlayerSelectionWidget::ChangePlayer2()
{
	if (this->Player2CharacterIndex == this->CharacterTypes.Num() - 1)
	{
		this->Player2CharacterIndex = 0;
	}
	else
	{
		this->Player2CharacterIndex++;
	}
	this->Player2Character = this->CharacterTypes[this->Player2CharacterIndex].GetDefaultObject();
	this->UpdatePlayer2();
}

void UPlayerSelectionWidget::UpdatePlayer1()
{
	this->Player1CharacterImage->SetBrushFromTexture(this->Player1Character->CharacterImage);
}

void UPlayerSelectionWidget::UpdatePlayer2()
{
	this->Player2CharacterImage->SetBrushFromTexture(this->Player2Character->CharacterImage);
}

void UPlayerSelectionWidget::GoBack()
{
	UGameplayStatics::OpenLevel(this, "/Game/Menus/MainMenu/MainMenu");
}

void UPlayerSelectionWidget::BeginGame()
{
	UGameplayStatics::OpenLevel(this, "/Game/DemoLevel");
}
