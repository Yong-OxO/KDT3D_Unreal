// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LobbyInputDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class KDT3D_API ULobbyInputDataAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	bool CheckValid();

public:
	UPROPERTY(EditAnywhere, Category = "Input|InputMappingContext")
	class UInputMappingContext* IMC_Default;

	UPROPERTY(EditAnywhere, Category = "Input|InputAction")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input|InputAction")
	class UInputAction* LookMouseAction;

	UPROPERTY(EditAnywhere, Category = "Input|InputAction")
	class UInputAction* ZoomWheelAction;

	UPROPERTY(EditAnywhere, Category = "Input|InputAction")
	class UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input|InputAction")
	class UInputAction* CrouchAction;
};
