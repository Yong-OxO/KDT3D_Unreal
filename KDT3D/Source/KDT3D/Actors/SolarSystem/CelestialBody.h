// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/CelestialBodyDataAsset.h"
#include "CelestialBody.generated.h"

UCLASS()
class KDT3D_API ACelestialBody : public AActor
{
	GENERATED_BODY()
	
public:	
	ACelestialBody();

	double GetOrbitalSpeed() const { return CelestialBodyData ? CelestialBodyData->OrbitalSpeed : 0.0; }
protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Destroyed() override;

	void OnCelestialBodyDataChanged();
	virtual void UpdateDataAsset();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// 공전축
	UPROPERTY(VisibleAnywhere)
	USceneComponent* OrbitalAxis;
	// 자전축
	UPROPERTY(VisibleAnywhere)
	USceneComponent* RotatingAxis;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Body;

	UPROPERTY() // Optinal
	UMaterialInstanceDynamic* BodyMID = nullptr;

protected: // Optinal
	UPROPERTY()
	UMaterialInstanceDynamic* BodyMID = nullptr;

protected: // Optinal
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Cloud;

protected:
	UPROPERTY(Transient)
	class AStar* ChachedStar = nullptr;

protected:
#if WITH_EDITOR
	virtual void PreEditChange(FProperty* PropertyAboutToChange) override;
#endif

protected:
	UPROPERTY(Category = "CelestialBody", EditAnywhere)
	UCelestialBodyDataAsset* CelestialBodyData;
	FDelegateHandle CelestialBodyDataUpdateHandle;


};
