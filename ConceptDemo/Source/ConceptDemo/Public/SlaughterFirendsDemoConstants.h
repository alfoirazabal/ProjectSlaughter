// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <UObject/Class.h>

UENUM()
enum FACING_DIRECTION {
	RIGHT	UMETA(DisplayName = "Right"),
	LEFT	UMETA(DisplayName = "Left")
};

/**
 * 
 */
class CONCEPTDEMO_API SlaughterFirendsDemoConstants
{
public:
	SlaughterFirendsDemoConstants();
	~SlaughterFirendsDemoConstants();
};
