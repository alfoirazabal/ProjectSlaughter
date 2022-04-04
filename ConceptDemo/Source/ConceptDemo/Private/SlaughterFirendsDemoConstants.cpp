// Fill out your copyright notice in the Description page of Project Settings.


#include "SlaughterFirendsDemoConstants.h"

SlaughterFirendsDemoConstants::SlaughterFirendsDemoConstants()
{
}

float SlaughterFirendsDemoConstants::GenerateBoundedFloat(float min, float max)
{
	return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

SlaughterFirendsDemoConstants::~SlaughterFirendsDemoConstants()
{
}
