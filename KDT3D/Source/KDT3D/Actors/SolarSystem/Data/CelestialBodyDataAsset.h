// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CelestialBodyDataAsset.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnCelestialBodyDataAssetChanged)

/**
 * 
 */
UCLASS()
class KDT3D_API UCelestialBodyDataAsset : public UDataAsset
{
	GENERATED_BODY()

public: // Body
	UPROPERTY(EditAnywhere, Category = "CelestialBody")
	FVector BodyScale3D = FVector(1.0, 1.0, 1.0);

	UPROPERTY(EditAnywhere, Category = "CelestialBody")
	UStaticMesh* BodyMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "CelestialBody")
	UMaterial* BodyMaterial = nullptr;


	UPROPERTY(EditAnywhere, Category = "CelestialBody")
	double OrbitalSpeed = 45.0;

	UPROPERTY(EditAnywhere, Category = "CelestialBody")
	double RotatingSpeed = 60.0;
	
public: //Cloud
	UPROPERTY(EditAnywhere, Category = "CelestialBody|Cloud")
	bool bCloud = false;

	UPROPERTY(EditAnywhere, Category = "CelestialBody|Cloud")
	UStaticMesh* CloudMesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "CelestialBody|Cloud")
	UMaterial* CloudMaterial = nullptr;

	UPROPERTY(EditAnywhere, Category = "CelestialBody|Cloud")
	FVector CloudScale3D = FVector(BodyScale3D.X * 1.02, BodyScale3D.Y * 1.02, BodyScale3D.Z * 1.02);

	UPROPERTY(EditAnywhere, Category = "CelestialBody|Cloud")
	double CloudRotatingSpeed = 60.0;

	UPROPERTY(EditAnywhere, Category = "CelestialBody|Cloud")
	UMaterial* OverlayMaterial = nullptr;

	UPROPERTY(EditAnywhere, Category = "CelestialBody|Cloud")
	FLinearColor OverlayColor = FLinearColor(0.25, 0.3, 1.0, 1.0);

public:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	FOnCelestialBodyDataAssetChanged OnCelestialBodyDataAssetChanged;
#endif
};
