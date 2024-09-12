// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "LobbyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class KDT3D_API ULobbyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
protected:
	UPROPERTY()
	class UPawnMovementComponent* MovementComponent;

	UPROPERTY(BlueprintReadOnly)
	double GroundSpeed = 0.0;

	UPROPERTY(BlueprintReadOnly)
	bool bIsCrouch = false;

	UPROPERTY(BlueprintReadOnly)
	bool bIsFalling = false;
};
