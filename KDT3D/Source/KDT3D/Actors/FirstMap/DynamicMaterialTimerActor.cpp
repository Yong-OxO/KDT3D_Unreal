// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/FirstMap/DynamicMaterialTimerActor.h"
#include "Kismet/KismetSystemLibrary.h"


void ADynamicMaterialTimerActor::BeginPlay()
{
	Super::BeginPlay();

	UKismetSystemLibrary::K2_SetTimer(this, TEXT("OnTimer"), 1.f, true);
}

void ADynamicMaterialTimerActor::OnTimer()
{
	static FLinearColor ColorTable[3] = { FLinearColor::Red, FLinearColor::Green, FLinearColor::Blue };

	MID->SetVectorParameterValue(TEXT("BaseColor"), ColorTable[ColorIndex]);
	//ColorIndex = FMath::Wrap(ColorIndex + 1, 0, 2);
	ColorIndex = ColorIndex + 1;
	ColorIndex = ColorIndex % 3;
}
