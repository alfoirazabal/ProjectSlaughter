// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <UObject/Class.h>

UENUM()
enum FACING_DIRECTION {
	RIGHT	UMETA(DisplayName = "Right"),
	LEFT	UMETA(DisplayName = "Left")
};

const int levelsZFallLimit = -1000;

/**
 * 
 */
class CONCEPTDEMO_API SlaughterFirendsDemoConstants
{
public:
	SlaughterFirendsDemoConstants();
	~SlaughterFirendsDemoConstants();

	float GenerateBoundedFloat(float min, float max);
};
