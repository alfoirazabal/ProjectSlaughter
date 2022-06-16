// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class CONCEPTDEMO_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget)) UTextBlock* TxtVersionText;

	UFUNCTION() virtual void NativeConstruct() override;
	
};
