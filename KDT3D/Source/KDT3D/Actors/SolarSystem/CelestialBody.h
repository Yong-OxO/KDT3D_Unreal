// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CelestialBody.generated.h"

class AStar;
class UCelestialBodyDataAsset;


UCLASS()
class KDT3D_API ACelestialBody : public AActor
{
	GENERATED_BODY()

public:	
	ACelestialBody();

	double GetOrbitalSpeed() const;
	void SetCelestialBodyData(UCelestialBodyDataAsset* InData);

protected:
	virtual void BeginPlay() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Destroyed() override;

	void OnCelestialBodyDataChanged();
	virtual void UpdateDataAsset();

	void CalculateStarLightDirection();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector GetBodyWorldLocation() const { return Body->GetComponentLocation(); }

protected:
	// 공전축
	UPROPERTY(VisibleAnywhere)
	USceneComponent* OrbitalAxis;
	// 자전축
	UPROPERTY(VisibleAnywhere)
	USceneComponent* RotatingAxis;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Body;

protected: // Optinal
	UPROPERTY()
	UMaterialInstanceDynamic* BodyMID = nullptr;

protected: // Optinal
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Cloud;

protected:
	UPROPERTY(Transient)
	AStar* ChachedStar = nullptr;

protected:
#if WITH_EDITOR
	virtual void PreEditChange(FProperty* PropertyAboutToChange) override;
#endif

protected:
	UPROPERTY(Category = "CelestialBody", EditAnywhere)
	UCelestialBodyDataAsset* CelestialBodyData;
	FDelegateHandle CelestialBodyDataUpdateHandle;
};
