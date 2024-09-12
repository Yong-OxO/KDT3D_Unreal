// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Lobby/Components/SoftWheelSpringArmComponent.h"




void USoftWheelSpringArmComponent::ZoomWheel(const float ActionValue)
{
	DesiredTargetArmLength = FMath::Clamp(DesiredTargetArmLength + ActionValue, MinTargetArmLength, MaxTargetArmLength);
}

void USoftWheelSpringArmComponent::UpdateDesiredArmTargetLength(const float DeltaTime)
{
	if (FMath::IsNearlyEqual(TargetArmLength, DesiredTargetArmLength)) { return; }

	const float DeltaSpeed = FMath::Clamp(DeltaTime * WheelSpeed, 0.f, 1.f);
	TargetArmLength = FMath::Lerp(TargetArmLength, DesiredTargetArmLength, DeltaSpeed);
	TargetArmLength = FMath::Clamp(TargetArmLength, MinTargetArmLength, MaxTargetArmLength);
}

void USoftWheelSpringArmComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UpdateDesiredArmTargetLength(DeltaTime);
}

void USoftWheelSpringArmComponent::SetMinTargetArmLength(const float MinLength)
{
	if (MinLength > MaxTargetArmLength || MinLength > TargetArmLength)
	{
		checkf(false, TEXT("Set MinLength Error"));
		return;
	}
	MinTargetArmLength = MinLength;
	DesiredTargetArmLength = TargetArmLength;
}

void USoftWheelSpringArmComponent::SetMaxTargetArmLength(const float MaxLength)
{
	if (MaxLength < MinTargetArmLength || MaxLength < TargetArmLength)
	{
		checkf(false, TEXT("Set MaxLength Error"));
		return;
	}
	MaxTargetArmLength = MaxLength;
	DesiredTargetArmLength = TargetArmLength;
}


