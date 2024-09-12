// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "SoftWheelSpringArmComponent.generated.h"

/**
 * 
 */
UCLASS()
class KDT3D_API USoftWheelSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()
	
public:
	void ZoomWheel(const float ActionValue);

	void SetMinTargetArmLength(const float MinLength);
	void SetMaxTargetArmLength(const float MaxLength);

	float GetMinTargetArmLength() const { return MinTargetArmLength; }
	float GetMaxTargetArmLength() const { return MaxTargetArmLength; }

protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	void UpdateDesiredArmTargetLength(const float DeltaTime);

protected:
	float MinTargetArmLength = 200.f;
	float MaxTargetArmLength = 800.f;

	float DesiredTargetArmLength = TargetArmLength;

	float WheelSpeed = 5.f;
};
