// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SolarSystem/SolarSystemPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Kismet/GameplayStatics.h"

void ASolarSystemPlayerController::Tick(float DeltaTime)
{
}

void ASolarSystemPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(MappingContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);

	Subsystem->AddMappingContext(MappingContext, 0);
}

void ASolarSystemPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(StartAction, ETriggerEvent::Started, this, &ASolarSystemPlayerController::StartGame);
}

void ASolarSystemPlayerController::StartGame()
{ 
	UE_LOG(LogTemp, Display, TEXT("LClick"));
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("FirstMap"));
	return;
}

