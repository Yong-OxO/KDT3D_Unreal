// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SolarSystem.generated.h"



UCLASS()
class KDT3D_API ASolarSystem : public AActor
{
	GENERATED_BODY()
public:
	class UStarDataAsset;
	class APlanet;

	ASolarSystem();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;

	void UpdateStarData();

protected:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* DefaultSceneRoot = nullptr;

	UPROPERTY(VisibleAnywhere)
	UChildActorComponent* StarChildActorComponent;

	UPROPERTY(EditAnywhere)
	UStarDataAsset* StarBodyData;

	UPROPERTY(EditAnywhere)
	TArray<APlanet*> Planets;

};
