// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Lobby/LobbyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"

#include "Components/SoftWheelSpringArmComponent.h"

ALobbyCharacter::ALobbyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = GetCharacterMovement();
	MovementComponent->bOrientRotationToMovement = false;

	SpringArm = CreateDefaultSubobject<USoftWheelSpringArmComponent>(TEXT("SpringArm"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	{
		SpringArm->SetupAttachment(RootComponent);
		SpringArm->ProbeSize = 5.0;
		SpringArm->bUsePawnControlRotation = true;
		SpringArm->bInheritRoll = false;
	}
	Camera->SetupAttachment(SpringArm);

	UCharacterMovementComponent* Movement = GetCharacterMovement();
	Movement->RotationRate = FRotator(0.0, 720.0, 0.0);
	Movement->bOrientRotationToMovement = true;

	GetCapsuleComponent()->SetCapsuleHalfHeight(90.f, false);

	{
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> ObjectFinder(TEXT("/Script/Engine.SkeletalMesh'/Game/ParagonWraith/Characters/Heroes/Wraith/Meshes/Wraith.Wraith'"));
		check(ObjectFinder.Object);
		USkeletalMeshComponent* SkeletalMeshComponent = GetMesh();
		SkeletalMeshComponent->SetSkeletalMesh(ObjectFinder.Object);

		const FRotator Rotation = FRotator(0., -90.0, 0.);
		const FVector Translation = FVector(0., 0., -90.0);
		const FTransform Transform = FTransform(Rotation, Translation, FVector::OneVector);
		SkeletalMeshComponent->SetRelativeTransform(Transform);
	}

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ALobbyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALobbyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALobbyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

