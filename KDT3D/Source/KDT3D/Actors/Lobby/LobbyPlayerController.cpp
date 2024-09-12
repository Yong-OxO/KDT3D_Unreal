// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Lobby/LobbyPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"

#include "Components/SoftWheelSpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "Actors/Lobby/LobbyCharacter.h"
#include "LobbyInputDataAsset.h"




ALobbyPlayerController::ALobbyPlayerController()
{
	ConstructorHelpers::FObjectFinder<ULobbyInputDataAsset> ObjectDataAsset(TEXT("/Script/KDT3D.LobbyInputDataAsset'/Game/Blueprint/Lobby/GameplayFramework/Data/DA_LobbyInput.DA_LobbyInput'"));
	LobbyInputDataAsset = ObjectDataAsset.Object;
	LobbyInputDataAsset->CheckValid();
}

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ControlledCharacter = CastChecked<ALobbyCharacter>(GetPawn());

	UEnhancedInputLocalPlayerSubsystem* LocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(LocalPlayerSubsystem);
	LocalPlayerSubsystem->AddMappingContext(LobbyInputDataAsset->IMC_Default, 0);
}

void ALobbyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(LobbyInputDataAsset->MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInputComponent->BindAction(LobbyInputDataAsset->LookMouseAction, ETriggerEvent::Triggered, this, &ThisClass::LookMouse);
	EnhancedInputComponent->BindAction(LobbyInputDataAsset->ZoomWheelAction, ETriggerEvent::Triggered, this, &ThisClass::ZoomWheel);
	EnhancedInputComponent->BindAction(LobbyInputDataAsset->JumpAction, ETriggerEvent::Triggered, this, &ThisClass::Jump);
	EnhancedInputComponent->BindAction(LobbyInputDataAsset->JumpAction, ETriggerEvent::Completed, this, &ThisClass::StopJump);
	EnhancedInputComponent->BindAction(LobbyInputDataAsset->CrouchAction, ETriggerEvent::Triggered, this, &ThisClass::Crouch); 
	EnhancedInputComponent->BindAction(LobbyInputDataAsset->CrouchAction, ETriggerEvent::Completed, this, &ThisClass::StopCrouch);
}

void ALobbyPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator RotationYaw(0.0, Rotation.Yaw, 0.0);
	const FVector FowardVector = UKismetMathLibrary::GetForwardVector(RotationYaw);
	const FVector RightVector = UKismetMathLibrary::GetRightVector(RotationYaw);

	ControlledCharacter = CastChecked<ALobbyCharacter>(GetPawn());
	ControlledCharacter->AddMovementInput(FowardVector, InputVector.X);
	ControlledCharacter->AddMovementInput(RightVector, InputVector.Y);
}

void ALobbyPlayerController::LookMouse(const FInputActionValue& InputActionValue)
{
	const FVector2D ActionValue = InputActionValue.Get<FVector2D>();

	AddYawInput(ActionValue.X);
	AddPitchInput(ActionValue.Y);
}

void ALobbyPlayerController::ZoomWheel(const FInputActionValue& InputActionValue)
{
	ControlledCharacter = CastChecked<ALobbyCharacter>(GetPawn());
	USoftWheelSpringArmComponent* SpringArm = ControlledCharacter->GetComponentByClass<USoftWheelSpringArmComponent>();
	
	float ActionValue = InputActionValue.Get<float>();

	SpringArm->ZoomWheel(ActionValue * 20.f);
}

void ALobbyPlayerController::Jump(const FInputActionValue& InputActionValue)
{
	ControlledCharacter = CastChecked<ALobbyCharacter>(GetPawn());
	ControlledCharacter->Jump();
}

void ALobbyPlayerController::StopJump(const FInputActionValue& InputActionValue)
{
	ControlledCharacter = CastChecked<ALobbyCharacter>(GetPawn());
	ControlledCharacter->StopJumping();
}

void ALobbyPlayerController::Crouch(const FInputActionValue& InputActionValue)
{
	ControlledCharacter = CastChecked<ALobbyCharacter>(GetPawn());
	if (ControlledCharacter->GetMovementComponent()->IsFalling()) { return; }
	ControlledCharacter->Crouch();
}

void ALobbyPlayerController::StopCrouch(const FInputActionValue& InputActionValue)
{
	ControlledCharacter = CastChecked<ALobbyCharacter>(GetPawn());
	ControlledCharacter->UnCrouch();
}
