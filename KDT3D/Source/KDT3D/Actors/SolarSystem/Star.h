// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/SolarSystem/CelestialBody.h"
#include "Components/TimelineComponent.h"
#include "Star.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnStarDataAssetChanged)

UCLASS()
class KDT3D_API AStar : public ACelestialBody
{
	GENERATED_BODY()

public:
	AStar();
#if WITH_EDITOR
	FOnStarDataAssetChanged OnStarDataAssetChanged;
#endif

protected:
	virtual void UpdateDataAsset() override;
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnStarPower(float Value);


protected:
	UPROPERTY()
	class UStarDataAsset* StarBodyData;

	UPROPERTY()
	class UPointLightComponent* PointLight;

	UPROPERTY()
	UTimelineComponent* StarEmissivePowerTimelineComponent;

protected:
	UPROPERTY()
	UMaterialInstanceDynamic* MID = nullptr;

protected:
	const static inline FName TrackName = TEXT("Value");
	const static inline FName MID_EmissivePower = TEXT("EmissivePower");
};
