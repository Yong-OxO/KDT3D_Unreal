// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "SolarSystemInputDataAsset.generated.h"

class UInputMappingContext;
class UInputAction;


UCLASS()
class KDT3D_API USolarSystemInputDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "Input|InputMappingContext")
	UInputMappingContext* IMC_SolarSystem;

	UPROPERTY(EditAnywhere, Category = "Input|Action")
	UInputAction* StartAction;
};
