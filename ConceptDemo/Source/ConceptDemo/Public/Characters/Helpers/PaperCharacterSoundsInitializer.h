// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacterSounds.h"
#include "UObject/NoExportTypes.h"
#include "PaperCharacterSoundsInitializer.generated.h"

/**
 * 
 */
UCLASS()
class CONCEPTDEMO_API UPaperCharacterSoundsInitializer : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION() void InitializeDefaultSounds(FPaperCharacterSounds& PaperCharacterSounds);
	
};
