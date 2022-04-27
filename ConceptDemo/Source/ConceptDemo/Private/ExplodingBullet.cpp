// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplodingBullet.h"

AExplodingBullet::AExplodingBullet()
{
	this->DamageRadiusSize = 10;
	this->DamageDecreasesWithRadius = false;
	this->CurrentDamageRadiusSize = 1;
	this->InflationSpeed = 0.25;
	this->InitialDamage = this->ExplosionDamage;
}

void AExplodingBullet::Tick(const float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	this->CurrentDamageRadiusSize += this->InflationSpeed;
	this->SetActorScale3D(FVector(this->CurrentDamageRadiusSize, this->CurrentDamageRadiusSize, this->CurrentDamageRadiusSize));
	if (this->DamageDecreasesWithRadius)
	{
		const float NewBulletDamage = (this->DamageRadiusSize - this->CurrentDamageRadiusSize) / this->DamageRadiusSize;
		this->ExplosionDamage -= NewBulletDamage;
	}
	if (this->CurrentDamageRadiusSize >= this->DamageRadiusSize)
	{
		this->Destroy();
	}
}
