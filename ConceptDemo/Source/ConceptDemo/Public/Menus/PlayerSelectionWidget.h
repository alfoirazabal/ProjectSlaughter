// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/ConceptDemoPaperCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/Image.h"
#include "Components/RichTextBlock.h"
#include "PlayerSelectionWidget.generated.h"

/**
 * 
 */
UCLASS()
class CONCEPTDEMO_API UPlayerSelectionWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY() TArray<TSubclassOf<AConceptDemoPaperCharacter>> CharacterTypes;
	UPROPERTY() TArray<AConceptDemoPaperCharacter*> P1Characters;
	UPROPERTY() TArray<AConceptDemoPaperCharacter*> P2Characters;
	UPROPERTY() AConceptDemoPaperCharacter* Player1Character;
	UPROPERTY() AConceptDemoPaperCharacter* Player2Character;

public:
	
	UPROPERTY(EditAnywhere) TArray<UTexture2D*> BackgroundTextureSequence;
	UPROPERTY(EditAnywhere) float BackgroundTextureSequenceFlipTime;

	UPROPERTY() TArray<UImage*> P1CharacterImages;
	UPROPERTY() TArray<UImage*> P2CharacterImages;
	UPROPERTY() TArray<UImage*> P1SelectionMarkerImages;
	UPROPERTY() TArray<UImage*> P2SelectionMarkerImages;

    UPROPERTY(meta = (BindWidget)) UImage* BackgroundImage;

	UPROPERTY(meta = (BindWidget)) UImage* ImgP1Pos1;
	UPROPERTY(meta = (BindWidget)) UImage* ImgP1Pos2;
	UPROPERTY(meta = (BindWidget)) UImage* ImgP1Pos3;
	UPROPERTY(meta = (BindWidget)) UImage* ImgP1Pos4;
	UPROPERTY(meta = (BindWidget)) UImage* ImgP1Pos5;
	UPROPERTY(meta = (BindWidget)) UImage* ImgP1Pos6;
	UPROPERTY(meta = (BindWidget)) UImage* ImgP2Pos1;
	UPROPERTY(meta = (BindWidget)) UImage* ImgP2Pos2;
	UPROPERTY(meta = (BindWidget)) UImage* ImgP2Pos3;
	UPROPERTY(meta = (BindWidget)) UImage* ImgP2Pos4;
	UPROPERTY(meta = (BindWidget)) UImage* ImgP2Pos5;
	UPROPERTY(meta = (BindWidget)) UImage* ImgP2Pos6;

	UPROPERTY(meta = (BindWidget)) UImage* ImgSelectedP1Pos1;
	UPROPERTY(meta = (BindWidget)) UImage* ImgSelectedP1Pos2;
	UPROPERTY(meta = (BindWidget)) UImage* ImgSelectedP1Pos3;
	UPROPERTY(meta = (BindWidget)) UImage* ImgSelectedP1Pos4;
	UPROPERTY(meta = (BindWidget)) UImage* ImgSelectedP1Pos5;
	UPROPERTY(meta = (BindWidget)) UImage* ImgSelectedP1Pos6;
	UPROPERTY(meta = (BindWidget)) UImage* ImgSelectedP2Pos1;
	UPROPERTY(meta = (BindWidget)) UImage* ImgSelectedP2Pos2;
	UPROPERTY(meta = (BindWidget)) UImage* ImgSelectedP2Pos3;
	UPROPERTY(meta = (BindWidget)) UImage* ImgSelectedP2Pos4;
	UPROPERTY(meta = (BindWidget)) UImage* ImgSelectedP2Pos5;
	UPROPERTY(meta = (BindWidget)) UImage* ImgSelectedP2Pos6;

	UPROPERTY(meta = (BindWidget)) URichTextBlock* RichTextBlockPlayer1Description;
	UPROPERTY(meta = (BindWidget)) URichTextBlock* RichTextBlockPlayer2Description;
	UPROPERTY(meta = (BindWidget)) UEditableTextBox* EditableTextBoxPlayer1Name;
	UPROPERTY(meta = (BindWidget)) UEditableTextBox* EditableTextBoxPlayer2Name;

	UPROPERTY(meta = (BindWidget)) UButton* ButtonBegin;

	explicit UPlayerSelectionWidget(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION() void GoBack();
	UFUNCTION() void BeginGame();

protected:
	UPROPERTY() int CurrentFlippingImageIndex;
	UPROPERTY() FTimerHandle BackgroundImageFlippingTimer; 
	UFUNCTION() void SetBackgroundImageFlipping();

	UFUNCTION() void P1SelectLeftwardsPlayer();
	UFUNCTION() void P1SelectUpwardsPlayer();
	UFUNCTION() void P1SelectRightwardsPlayer();
	UFUNCTION() void P1SelectDownwardsPlayer();
	UFUNCTION() void P2SelectLeftwardsPlayer();
	UFUNCTION() void P2SelectUpwardsPlayer();
	UFUNCTION() void P2SelectRightwardsPlayer();
	UFUNCTION() void P2SelectDownwardsPlayer();

	UFUNCTION() void DisplaySelectedP1();
	UFUNCTION() void DisplaySelectedP2();
};
