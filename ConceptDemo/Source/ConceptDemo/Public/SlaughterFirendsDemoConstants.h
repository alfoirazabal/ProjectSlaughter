// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM()
enum EFacing_Direction {
	Right	UMETA(DisplayName = "Right"),
	Left	UMETA(DisplayName = "Left")
};

constexpr int GLevelsZFallLimit = -1000;

/**
 * 
 */
class CONCEPTDEMO_API SlaughterFirendsDemoConstants
{
public:
	SlaughterFirendsDemoConstants();
	~SlaughterFirendsDemoConstants();

	static float GenerateBoundedFloat(float Min, float Max);
};
