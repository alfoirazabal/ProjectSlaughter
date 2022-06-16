// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Rabbit/RabbitVioletPaperCharacter.h"

ARabbitVioletPaperCharacter::ARabbitVioletPaperCharacter()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> CharacterImageObject(TEXT("/Game/Character/Rabbit/Violet/Images/Idle/Comp_100"));
	this->CharacterImage = CharacterImageObject.Object;
	static ConstructorHelpers::FObjectFinder<UTexture2D> CharacterFaceImageObject(TEXT("/Game/Character/Rabbit/Violet/Images/BlasterH2"));
	this->CharacterFaceImage = CharacterFaceImageObject.Object;
}
