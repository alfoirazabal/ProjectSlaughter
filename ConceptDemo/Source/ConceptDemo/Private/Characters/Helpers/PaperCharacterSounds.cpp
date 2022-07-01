// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Helpers/PaperCharacterSounds.h"

UPaperCharacterSounds::UPaperCharacterSounds()
{
	static ConstructorHelpers::FObjectFinder<USoundBase> PowerUpReadySoundObject(TEXT("/Game/Sounds/AbilityReady"));
	this->PowerUpReadySound = PowerUpReadySoundObject.Object;
	
	static ConstructorHelpers::FObjectFinder<USoundBase> DamageTakenSound1(TEXT("/Game/Sounds/damage/damage_1"));
	static ConstructorHelpers::FObjectFinder<USoundBase> DamageTakenSound2(TEXT("/Game/Sounds/damage/damage_2"));
	static ConstructorHelpers::FObjectFinder<USoundBase> DamageTakenSound3(TEXT("/Game/Sounds/damage/damage_3"));
	static ConstructorHelpers::FObjectFinder<USoundBase> DamageTakenSound4(TEXT("/Game/Sounds/damage/damage_4"));
	static ConstructorHelpers::FObjectFinder<USoundBase> DamageTakenSound5(TEXT("/Game/Sounds/damage/damage_5"));
	this->DamageTaken.Add(DamageTakenSound1.Object);
	this->DamageTaken.Add(DamageTakenSound2.Object);
	this->DamageTaken.Add(DamageTakenSound3.Object);
	this->DamageTaken.Add(DamageTakenSound4.Object);
	this->DamageTaken.Add(DamageTakenSound5.Object);
	
	static ConstructorHelpers::FObjectFinder<USoundBase> TakeAGunSoundObject(TEXT("/Game/Sounds/take_a_gun_"));
	static ConstructorHelpers::FObjectFinder<USoundBase> TakeALifeSoundObject(TEXT("/Game/Sounds/take_a_life"));
	this->TakeGun = TakeAGunSoundObject.Object;
	this->TakeLife = TakeALifeSoundObject.Object;
}
