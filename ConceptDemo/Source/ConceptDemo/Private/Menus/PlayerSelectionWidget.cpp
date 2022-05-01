// Fill out your copyright notice in the Description page of Project Settings.


#include "Menus/PlayerSelectionWidget.h"

#include "DemoGameInstance.h"
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
		this->Characters.Reserve(this->CharacterTypes.Num());
		for (TSubclassOf<AUConceptDemoPaperCharacter> ConceptDemoPaperCharacter : this->CharacterTypes)
		{
			this->Characters.Add(ConceptDemoPaperCharacter.GetDefaultObject());
		}
		this->Player1CharacterIndex = FMath::RandRange(0, this->Characters.Num() - 1);
		this->Player2CharacterIndex = FMath::RandRange(0, this->Characters.Num() - 1);
		this->Player1Character = this->Characters[this->Player1CharacterIndex];
		this->Player2Character = this->Characters[this->Player2CharacterIndex];
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
	if (this->Player1CharacterIndex == this->Characters.Num() - 1)
	{
		this->Player1CharacterIndex = 0;
	}
	else
	{
		this->Player1CharacterIndex++;
	}
	this->Player1Character = this->Characters[this->Player1CharacterIndex];
	this->UpdatePlayer1();
}

void UPlayerSelectionWidget::ChangePlayer2()
{
	if (this->Player2CharacterIndex == this->Characters.Num() - 1)
	{
		this->Player2CharacterIndex = 0;
	}
	else
	{
		this->Player2CharacterIndex++;
	}
	this->Player2Character = this->Characters[this->Player2CharacterIndex];
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
	GEngine->AddOnScreenDebugMessage(287572113, 2, FColor::Green, "Implemented on Blueprints");
}

void UPlayerSelectionWidget::BeginGame()
{
	UDemoGameInstance* GameInstance = Cast<UDemoGameInstance>(this->GetGameInstance());
	UClass* Player1CharacterClass = this->Player1Character->GetClass();
	UClass* Player2CharacterClass = this->Player2Character->GetClass();
	if (IsValid(Player1CharacterClass)) GameInstance->SelectedPlayer1Type = Player1CharacterClass;
	if (IsValid(Player2CharacterClass)) GameInstance->SelectedPlayer2Type = Player2CharacterClass;
	GameInstance->Player1Name = this->EditableTextBoxPlayer1Name->Text;
	GameInstance->Player2Name = this->EditableTextBoxPlayer2Name->Text;
	UGameplayStatics::OpenLevel(this, "/Game/DemoLevel");
}
