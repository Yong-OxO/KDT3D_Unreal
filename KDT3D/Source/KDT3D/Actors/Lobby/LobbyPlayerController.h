// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"

struct FInputActionValue;
class KDT3D_API ULobbyInputDataAsset;


UCLASS()
class KDT3D_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ALobbyPlayerController();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY()
	class ALobbyCharacter* ControlledCharacter;

	UPROPERTY()
	ULobbyInputDataAsset* LobbyInputDataAsset;

private:
	void Move(const FInputActionValue& InputActionValue);
	void LookMouse(const FInputActionValue& InputActionValue);
	void ZoomWheel(const FInputActionValue& InputActionValue);
	void Jump(const FInputActionValue& InputActionValue);
	void StopJump(const FInputActionValue& InputActionValue);
	void Crouch(const FInputActionValue& InputActionValue);
	void StopCrouch(const FInputActionValue& InputActionValue);
};
