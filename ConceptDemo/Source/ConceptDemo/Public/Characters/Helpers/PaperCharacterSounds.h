// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacterSounds.generated.h"

/**
 * 
 */
USTRUCT()
struct CONCEPTDEMO_API FPaperCharacterSounds
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="Sounds") USoundBase* PowerUpReadySound;
	UPROPERTY(EditAnywhere, Category="Sounds") USoundBase* CriticalDamage;
	UPROPERTY(EditAnywhere, Category="Sounds") USoundBase* DeathByTrap;
	UPROPERTY(EditAnywhere, Category="Sounds") USoundBase* Kill;
	UPROPERTY(EditAnywhere, Category="Sounds") USoundBase* Select;
	UPROPERTY(EditAnywhere, Category="Sounds") USoundBase* Spawn;
	UPROPERTY(EditAnywhere, Category="Sounds") USoundBase* SpecialSkill;
	UPROPERTY(EditAnywhere, Category="Sounds") USoundBase* TakeGunOrLife;
	UPROPERTY(EditAnywhere, Category="Sounds") USoundBase* TakeGun;
	UPROPERTY(EditAnywhere, Category="Sounds") USoundBase* TakeLife;
	UPROPERTY(EditAnywhere, Category="Sounds") TArray<USoundBase*> DamageTaken;
	
};
