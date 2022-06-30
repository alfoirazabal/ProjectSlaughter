// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Props/Droppables/Droppable.h"

#include "UPaperCharacterDroppables.generated.h"

/**
 * 
 */
UCLASS() class CONCEPTDEMO_API UPaperCharacterDroppables : public UObject
{
	GENERATED_BODY()
	
public:
	
	UPaperCharacterDroppables();

	UFUNCTION() TArray<TSubclassOf<ADroppable>> GetDroppables();
	
};
