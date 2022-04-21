// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConceptDemoPaperCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/Image.h"
#include "PlayerSelectionWidget.generated.h"

/**
 * 
 */
UCLASS()
class CONCEPTDEMO_API UPlayerSelectionWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TArray<TSubclassOf<AUConceptDemoPaperCharacter>> CharacterTypes;
	UPROPERTY() TArray<AUConceptDemoPaperCharacter*> Characters;
	UPROPERTY(EditAnywhere) AUConceptDemoPaperCharacter* Player1Character;
	UPROPERTY(EditAnywhere) AUConceptDemoPaperCharacter* Player2Character;
	uint16 Player1CharacterIndex;
	uint16 Player2CharacterIndex;

public:
	UPROPERTY(meta = (BindWidget)) UButton* ButtonGoBack;
	UPROPERTY(meta = (BindWidget)) UButton* ButtonBegin;
	UPROPERTY(meta = (BindWidget)) UButton* Player1ChangeButton;
	UPROPERTY(meta = (BindWidget)) UButton* Player2ChangeButton;
	UPROPERTY(meta = (BindWidget)) UImage* Player1CharacterImage;
	UPROPERTY(meta = (BindWidget)) UImage* Player2CharacterImage;
	UPROPERTY(meta = (BindWidget)) UEditableTextBox* EditableTextBoxPlayer1Name;
	UPROPERTY(meta = (BindWidget)) UEditableTextBox* EditableTextBoxPlayer2Name;

	virtual void NativeConstruct() override;

	UFUNCTION() void ChangePlayer1();
	UFUNCTION() void ChangePlayer2();
	void UpdatePlayer1();
	void UpdatePlayer2();
	UFUNCTION() void GoBack();
	UFUNCTION() void BeginGame();
	
};
