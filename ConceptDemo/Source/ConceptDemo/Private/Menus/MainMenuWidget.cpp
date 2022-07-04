// Fill out your copyright notice in the Description page of Project Settings.


#include "Menus/MainMenuWidget.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	this->TxtVersionText->SetText(FText::FromString("V 2022.07.03-2"));
}
