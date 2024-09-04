// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SolarSystem/SolarSystem.h"
#include "Planet.h"
#include "Star.h"
#include "Data/StarDataAsset.h"
#include "Data/CelestialBodyDataAsset.h"



// Sets default values
ASolarSystem::ASolarSystem()
{
 	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	StarChildActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("Star"));
	StarChildActorComponent->SetupAttachment(RootComponent);
	StarChildActorComponent->SetChildActorClass(AStar::StaticClass());
}

void ASolarSystem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	UpdateStarData();
}

// Called when the game starts or when spawned
void ASolarSystem::BeginPlay()
{
	Super::BeginPlay();	
}

void ASolarSystem::UpdateStarData()
{
	AStar* Star = Cast<AStar>(StarChildActorComponent->GetChildActor());
	if (Star && StarBodyData)
	{
		Star->SetCelestialBodyData(StarBodyData);
	}
}

#if WITH_EDITOR
void ASolarSystem::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	UpdateStarData();
}
#endif 
// Called every frame
void ASolarSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

