// Fill out your copyright notice in the Description page of Project Settings.


#include "Levels/UserWidgetPlayersStatus.h"

void UUserWidgetPlayersStatus::NativeConstruct()
{
	Super::NativeConstruct();
	this->PbrP1Life->SetPercent(1);
	this->PbrP2Life->SetPercent(1);
	this->PbrP1Stamina->SetPercent(0);
	this->PbrP2Stamina->SetPercent(0);
}
