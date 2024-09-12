// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Lobby/Animation/LobbyAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void ULobbyAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	APawn* Pawn = TryGetPawnOwner();
	if (GIsEditor && FApp::IsGame() && !Pawn)
	{
		check(false);
		return;
	}
	else if (!Pawn)	{ return; }

	MovementComponent = Pawn->GetMovementComponent();
	check(MovementComponent);
}

void ULobbyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!MovementComponent) { return; }

	GroundSpeed = UKismetMathLibrary::VSizeXY(MovementComponent->Velocity);
	
	bIsCrouch = MovementComponent->IsCrouching();
	bIsFalling = MovementComponent->IsFalling();
}
