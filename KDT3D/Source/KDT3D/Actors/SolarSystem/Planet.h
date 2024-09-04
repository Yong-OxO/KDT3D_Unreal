// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/SolarSystem/CelestialBody.h"
#include "Planet.generated.h"

/**
 * 
 */
UCLASS()
class KDT3D_API APlanet : public ACelestialBody
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void Destroyed() override;

protected:
#if WITH_EDITOR
	virtual void PreEditChange(FProperty* PropertyAboutToChange) override;
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	TArray<ACelestialBody*> PrevMoons;
protected:
	ACelestialBody* AddMoon(ACelestialBody* InTemplate = nullptr);

protected:
	UPROPERTY(EditAnywhere)
	TArray<ACelestialBody*> Moons;

	
};
