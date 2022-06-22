// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Skunk/SkunkGreenPaperCharacter.h"

ASkunkGreenPaperCharacter::ASkunkGreenPaperCharacter()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> CharacterImageObject(TEXT("/Game/Character/Skunk/Images/Idle/Comp_100"));
	this->CharacterImage = CharacterImageObject.Object;
	static ConstructorHelpers::FObjectFinder<UTexture2D> CharacterFaceImageObject(TEXT("/Game/Character/Skunk/Images/marleyH1"));
	this->CharacterFaceImage = CharacterFaceImageObject.Object;
}
