// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Skunk/SkunkDarkPaperCharacter.h"

ASkunkDarkPaperCharacter::ASkunkDarkPaperCharacter()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> CharacterImageObject(TEXT("/Game/Character/SkunkAlt/Images/Idle/Comp_100"));
	this->CharacterImage = CharacterImageObject.Object;
	static ConstructorHelpers::FObjectFinder<UTexture2D> CharacterFaceImageObject(TEXT("/Game/Character/SkunkAlt/Images/marleyH2"));
	this->CharacterFaceImage = CharacterFaceImageObject.Object;
}
