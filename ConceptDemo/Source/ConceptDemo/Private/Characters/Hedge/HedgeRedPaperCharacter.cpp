// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Hedge/HedgeRedPaperCharacter.h"

AHedgeRedPaperCharacter::AHedgeRedPaperCharacter()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> CharacterImageObject(TEXT("/Game/Character/Hedge/Red/Images/Idle/Comp_100"));
	this->CharacterImage = CharacterImageObject.Object;
	static ConstructorHelpers::FObjectFinder<UTexture2D> CharacterFaceImageObject(TEXT("/Game/Character/Hedge/Red/Images/meedleH1"));
	this->CharacterFaceImage = CharacterFaceImageObject.Object;
}
