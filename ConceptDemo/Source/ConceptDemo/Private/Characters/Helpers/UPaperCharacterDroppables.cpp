// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Helpers/UPaperCharacterDroppables.h"

UPaperCharacterDroppables::UPaperCharacterDroppables()
{
	
}

TArray<TSubclassOf<ADroppable>> UPaperCharacterDroppables::GetDroppables()
{
	TArray<TSubclassOf<ADroppable>> Droppables;
	static ConstructorHelpers::FClassFinder<ADroppable> DroppableBone1OClassFinder(TEXT("/Game/Character/Droppables/DroppableBone1"));
	static ConstructorHelpers::FClassFinder<ADroppable> DroppableBone1_45D_OClassFinder(TEXT("/Game/Character/Droppables/DroppableBone1_45d"));
	static ConstructorHelpers::FClassFinder<ADroppable> DroppableBone1_90D_OClassFinder(TEXT("/Game/Character/Droppables/DroppableBone1_90d"));
	static ConstructorHelpers::FClassFinder<ADroppable> DroppableBone1_135D_OClassFinder(TEXT("/Game/Character/Droppables/DroppableBone1_135d"));
	static ConstructorHelpers::FClassFinder<ADroppable> DroppableBone2OClassFinder(TEXT("/Game/Character/Droppables/DroppableBone2"));
	static ConstructorHelpers::FClassFinder<ADroppable> DroppableBone2_45D_OClassFinder(TEXT("/Game/Character/Droppables/DroppableBone2_45d"));
	static ConstructorHelpers::FClassFinder<ADroppable> DroppableBone2_90D_OClassFinder(TEXT("/Game/Character/Droppables/DroppableBone2_90d"));
	static ConstructorHelpers::FClassFinder<ADroppable> DroppableBone2_135D_OClassFinder(TEXT("/Game/Character/Droppables/DroppableBone2_135d"));
	Droppables.Add(DroppableBone1OClassFinder.Class);
	Droppables.Add(DroppableBone1_45D_OClassFinder.Class);
	Droppables.Add(DroppableBone1_90D_OClassFinder.Class);
	Droppables.Add(DroppableBone1_135D_OClassFinder.Class);
	Droppables.Add(DroppableBone2OClassFinder.Class);
	Droppables.Add(DroppableBone2_45D_OClassFinder.Class);
	Droppables.Add(DroppableBone2_90D_OClassFinder.Class);
	Droppables.Add(DroppableBone2_135D_OClassFinder.Class);
	
	static ConstructorHelpers::FClassFinder<ADroppable> DroppableBloodSplat1ClassFinder(TEXT("/Game/Character/Droppables/DroppableBloodSplat1"));
	static ConstructorHelpers::FClassFinder<ADroppable> DroppableBloodSplat2ClassFinder(TEXT("/Game/Character/Droppables/DroppableBloodSplat2"));
	static ConstructorHelpers::FClassFinder<ADroppable> DroppableBloodSplat3ClassFinder(TEXT("/Game/Character/Droppables/DroppableBloodSplat3"));
	for (uint8 i = 0 ; i < 3 ; i++)
	{
		Droppables.Add(DroppableBloodSplat1ClassFinder.Class);
		Droppables.Add(DroppableBloodSplat2ClassFinder.Class);
		Droppables.Add(DroppableBloodSplat3ClassFinder.Class);
	}
	return Droppables;
}
