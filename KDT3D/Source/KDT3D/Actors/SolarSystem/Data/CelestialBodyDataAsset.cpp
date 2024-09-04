// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SolarSystem/Data/CelestialBodyDataAsset.h"

#if WITH_EDITOR
void UCelestialBodyDataAsset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	OnCelestialBodyDataAssetChanged.Broadcast();
}
#endif
