// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObjectWithChanceGenerator.generated.h"

/**
 * 
 */
UCLASS() class CONCEPTDEMO_API UObjectWithChanceGenerator : public UObject
{

	GENERATED_BODY()
	
protected:
	UPROPERTY() TArray<TSubclassOf<UObject>> Classes;
	UPROPERTY() TArray<float> ClassesSpawnChances;
	UPROPERTY() TArray<TSubclassOf<UObject>> SpawnChances;
	
public:
	UObjectWithChanceGenerator();

	UFUNCTION() void AddClass(TSubclassOf<UObject> Class, float SpawnChance);
	UFUNCTION() void BuildSpawnChances();
	UFUNCTION() TSubclassOf<UObject> GetRandomObjectClass();
	
};
