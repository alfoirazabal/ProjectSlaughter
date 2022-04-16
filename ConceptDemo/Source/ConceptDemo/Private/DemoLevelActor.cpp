// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoLevelActor.h"

void ADemoLevelActor::SetupInputs()
{
	this->InputComponent->BindAxis(TEXT("P1 HorizontalMovement"), this, &ADemoLevelActor::P1HorizontalMovement);
	this->InputComponent->BindAction(TEXT("P1 Jump"), IE_Pressed, this, &ADemoLevelActor::P1JumpPressed);
	this->InputComponent->BindAction(TEXT("P1 Jump"), IE_Released, this, &ADemoLevelActor::P1JumpReleased);
	this->InputComponent->BindAction(TEXT("P1 Drop Down"), IE_Pressed, this, &ADemoLevelActor::P1DropDownPressed);
	this->InputComponent->BindAction(TEXT("P1 Fire"), IE_Pressed, this, &ADemoLevelActor::P1Fire);
	this->InputComponent->BindAction(TEXT("P1 Drop Gun"), IE_Pressed, this, &ADemoLevelActor::P1DropGun);
	
	this->InputComponent->BindAxis(TEXT("P2 HorizontalMovement"), this, &ADemoLevelActor::P2HorizontalMovement);
	this->InputComponent->BindAction(TEXT("P2 Jump"), IE_Pressed, this, &ADemoLevelActor::P2JumpPressed);
	this->InputComponent->BindAction(TEXT("P2 Jump"), IE_Released, this, &ADemoLevelActor::P2JumpReleased);
	this->InputComponent->BindAction(TEXT("P2 Drop Down"), IE_Pressed, this, &ADemoLevelActor::P2DropDownPressed);
	this->InputComponent->BindAction(TEXT("P2 Fire"), IE_Pressed, this, &ADemoLevelActor::P2Fire);
	this->InputComponent->BindAction(TEXT("P2 Drop Gun"), IE_Pressed, this, &ADemoLevelActor::P2DropGun);
}

void ADemoLevelActor::P1HorizontalMovement(const float AxisValue)
{
	if (IsValid(this->Player1)) this->Player1->HandleMovement(AxisValue);
}

void ADemoLevelActor::P1JumpPressed()
{
	if (IsValid(this->Player1)) this->Player1->Jump();
}

void ADemoLevelActor::P1JumpReleased()
{
	if (IsValid(this->Player1)) this->Player1->HandleStopJump();
}

void ADemoLevelActor::P1DropDownPressed()
{
	if (IsValid(this->Player1)) this->Player1->DropDown();
}

void ADemoLevelActor::P1Fire()
{
	if (IsValid(this->Player1)) this->Player1->Fire();
}

void ADemoLevelActor::P1DropGun()
{
	if (IsValid(this->Player1)) this->Player1->DropGun();
}

void ADemoLevelActor::P2HorizontalMovement(const float AxisValue)
{
	if (IsValid(this->Player2)) this->Player2->HandleMovement(AxisValue);
}

void ADemoLevelActor::P2JumpPressed()
{
	if (IsValid(this->Player2)) this->Player2->Jump();
}

void ADemoLevelActor::P2JumpReleased()
{
	if (IsValid(this->Player2)) this->Player2->HandleStopJump();
}

void ADemoLevelActor::P2DropDownPressed()
{
	if (IsValid(this->Player2)) this->Player2->DropDown();
}

void ADemoLevelActor::P2Fire()
{
	if (IsValid(this->Player2)) this->Player2->Fire();
}

void ADemoLevelActor::P2DropGun()
{
	if (IsValid(this->Player2)) this->Player2->DropGun();
}