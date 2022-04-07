// Fill out your copyright notice in the Description page of Project Settings.


#include "SlaughterFirendsDemoConstants.h"

SlaughterFirendsDemoConstants::SlaughterFirendsDemoConstants()
{
}

float SlaughterFirendsDemoConstants::GenerateBoundedFloat(const float Min, const float Max)
{
	return Min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (Max - Min)));
}

SlaughterFirendsDemoConstants::~SlaughterFirendsDemoConstants()
{
}
