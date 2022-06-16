// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Hedge/HedgeBluePaperCharacter.h"

AHedgeBluePaperCharacter::AHedgeBluePaperCharacter()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> CharacterImageObject(TEXT("/Game/Character/Hedge/Blue/Images/Idle/Comp_100"));
	this->CharacterImage = CharacterImageObject.Object;
	static ConstructorHelpers::FObjectFinder<UTexture2D> CharacterFaceImageObject(TEXT("/Game/Character/Hedge/Blue/Images/meedleH2"));
	this->CharacterFaceImage = CharacterFaceImageObject.Object;
}
