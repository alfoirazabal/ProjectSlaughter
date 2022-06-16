// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Rabbit/RabbitYellowPaperCharacter.h"

ARabbitYellowPaperCharacter::ARabbitYellowPaperCharacter()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> CharacterImageObject(TEXT("/Game/Character/Rabbit/Yellow/Images/Idle/Comp_100"));
	this->CharacterImage = CharacterImageObject.Object;
	static ConstructorHelpers::FObjectFinder<UTexture2D> CharacterFaceImageObject(TEXT("/Game/Character/Rabbit/Yellow/Images/BlasterH1"));
	this->CharacterFaceImage = CharacterFaceImageObject.Object;
}
