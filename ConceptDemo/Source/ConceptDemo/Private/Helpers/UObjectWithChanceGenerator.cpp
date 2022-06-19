// Fill out your copyright notice in the Description page of Project Settings.


#include "Helpers/UObjectWithChanceGenerator.h"

UObjectWithChanceGenerator::UObjectWithChanceGenerator()
{
	this->SpawnChances.Reserve(100);
}

void UObjectWithChanceGenerator::AddClass(const TSubclassOf<UObject> Class, const float SpawnChance)
{
	this->Classes.Add(Class);
	this->ClassesSpawnChances.Add(SpawnChance);
}

void UObjectWithChanceGenerator::BuildSpawnChances()
{
	float TypesProbabilitySum = 0;
	for (int i = 0 ; i < this->Classes.Num() ; i++)
	{
		TypesProbabilitySum += this->ClassesSpawnChances[i];
	}
	for (int i = 0 ; i < 100 ; i++)
	{
		for (int j = 0 ; j < this->Classes.Num() ; j++)
		{
			const int TimesToAdd = (this->ClassesSpawnChances[j] / TypesProbabilitySum) * 100;
			for (int k = i ; k < TimesToAdd + i ; k++)
			{
				this->SpawnChances.Add(this->Classes[j]);
			}
		}
	}
}

TSubclassOf<UObject> UObjectWithChanceGenerator::GetRandomObjectClass()
{
	TSubclassOf<UObject> RandomSpawnType = nullptr;
	if (this->SpawnChances.Num() > 0)
	{
		const int RandomSpawnTypePosition = FMath::RandRange(0, this->SpawnChances.Num() - 1);
		RandomSpawnType = this->SpawnChances[RandomSpawnTypePosition];
	}
	return RandomSpawnType;
}

