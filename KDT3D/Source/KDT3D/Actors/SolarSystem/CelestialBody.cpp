#include "Actors/SolarSystem/CelestialBody.h"
#include "Actors/SolarSystem/Star.h"
#include "Kismet/GameplayStatics.h"
#include "Data/CelestialBodyDataAsset.h"
#include "Actors/SolarSystem/Star.h"


// Sets default values
ACelestialBody::ACelestialBody()
{
	PrimaryActorTick.bCanEverTick = true;

	OrbitalAxis = CreateDefaultSubobject<USceneComponent>(TEXT("OrbitalAxis"));
	RootComponent = OrbitalAxis;

	RotatingAxis = CreateDefaultSubobject<USceneComponent>(TEXT("RotatingAxis"));
	RotatingAxis->SetupAttachment(RootComponent);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RotatingAxis);
}

double ACelestialBody::GetOrbitalSpeed() const
{
	return CelestialBodyData ? CelestialBodyData->OrbitalSpeed : 0.0;
}

void ACelestialBody::SetCelestialBodyData(UCelestialBodyDataAsset* InData)
{
	CelestialBodyData = InData;
	OnConstruction(GetActorTransform());
}

// Called when the game starts or when spawned
void ACelestialBody::BeginPlay()
{
	Super::BeginPlay();
}

void ACelestialBody::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (CelestialBodyData)
	{
#if WITH_EDITOR
		CelestialBodyDataUpdateHandle = CelestialBodyData->OnCelestialBodyDataAssetChanged.AddUObject(this, &ThisClass::OnCelestialBodyDataChanged);
#endif
		UpdateDataAsset();
	}
}

void ACelestialBody::Destroyed()
{
	Super::Destroyed();
}

void ACelestialBody::OnCelestialBodyDataChanged()
{
	UpdateDataAsset();
}

void ACelestialBody::UpdateDataAsset()
{
	if (!CelestialBodyData) { return; }

	Body->SetStaticMesh(CelestialBodyData->BodyMesh);
	Body->SetMaterial(0, CelestialBodyData->BodyMaterial);
	Body->SetRelativeScale3D(CelestialBodyData->BodyScale3D);
	
	if (CelestialBodyData->BodyMaterial && CelestialBodyData->bMID)
	{
		BodyMID = Body->CreateDynamicMaterialInstance(0);
	}

	// Cloud, Atmosphere
	if (CelestialBodyData->bCloud && Cloud == nullptr)
	{
		Cloud = NewObject<UStaticMeshComponent>(this, TEXT("Cloud"));
		Cloud->RegisterComponent();
		Cloud->AttachToComponent(Body, FAttachmentTransformRules::KeepRelativeTransform);
	}
	if (CelestialBodyData->bCloud == false && Cloud)
	{
		Cloud->DestroyComponent();
		Cloud = nullptr;
	}
	if (Cloud)
	{
		Cloud->SetStaticMesh(CelestialBodyData->CloudMesh);
		Cloud->SetMaterial(0, CelestialBodyData->CloudMaterial);
		Cloud->SetRelativeScale3D(CelestialBodyData->CloudScale3D);

		UMaterialInterface* MaterialInterface = nullptr;
		if (CelestialBodyData->OverlayMaterial)
		{
			MaterialInterface = CelestialBodyData->OverlayMaterial;
			UMaterialInstanceDynamic* MID = Cast<UMaterialInstanceDynamic>(MaterialInterface);
			// 혹시 누군가 MaterialInterface에 MID 자료형을 넣어 놨을수도 있기 때문에 확인절차
			if (MaterialInterface && !MID)
			{
				MID = UMaterialInstanceDynamic::Create(MaterialInterface, Cloud, NAME_None);
				MaterialInterface = MID;

				MID->SetVectorParameterValue(TEXT("Color"), CelestialBodyData->OverlayColor);
			}
		}
		Cloud->SetOverlayMaterial(MaterialInterface);
	}

	if (CelestialBodyData->bCalculateStarLightDirection)
	{
		CalculateStarLightDirection();
	}
}

void ACelestialBody::CalculateStarLightDirection()
{
	if (!ChachedStar)
	{
		ChachedStar = Cast<AStar>(UGameplayStatics::GetActorOfClass(this, AStar::StaticClass()));
		if (!ChachedStar)
		{
			// 공간상에 Star가 없습니다.
			ensure(false);
			return;
		}
#if WITH_EDITOR
		ChachedStar->OnStarDataAssetChanged.AddUObject(this, &ThisClass::CalculateStarLightDirection);
#endif
	}

	const FVector MyLocation = GetBodyWorldLocation();
	const FVector StarLocation = ChachedStar->GetBodyWorldLocation();
	FVector DirectionVector = StarLocation - MyLocation;
	DirectionVector.Normalize();

	const FName MID_LightDirection = TEXT("LightDirection");
	BodyMID->SetVectorParameterValue(MID_LightDirection, DirectionVector);

	if (CelestialBodyData->OverlayMaterial && Cloud->OverlayMaterial)
	{
		UMaterialInstanceDynamic* MID = Cast<UMaterialInstanceDynamic>(Cloud->OverlayMaterial);
		if (MID)
		{
			MID->SetVectorParameterValue(MID_LightDirection, DirectionVector);
		}
	}
}

// Called every frame
void ACelestialBody::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!CelestialBodyData) { return; }

	{
		const double OrbitalSpeed = CelestialBodyData->OrbitalSpeed * DeltaTime;
		FRotator OrbitalRotator(0.0, OrbitalSpeed, 0.0);

		const double Speed = CelestialBodyData->RotatingSpeed * DeltaTime;
		FRotator Rotator(0.0, Speed, 0.0);

		OrbitalAxis->AddRelativeRotation(OrbitalRotator);
		Body->AddRelativeRotation(Rotator);
	}
	if (Cloud)
	{
		const double Speed = CelestialBodyData->CloudRotatingSpeed * DeltaTime;
		FRotator Rotator(0.0, Speed, 0.0);
		Cloud->AddRelativeRotation(Rotator);
	}

	if (CelestialBodyData->bCalculateStarLightDirection)
	{
		CalculateStarLightDirection();
	}
}

#if WITH_EDITOR
void ACelestialBody::PreEditChange(FProperty* PropertyAboutToChange)
{
	Super::PreEditChange(PropertyAboutToChange);

	const FString PropertyName = PropertyAboutToChange->GetName();
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, CelestialBodyData) && CelestialBodyData)
	{
		CelestialBodyData->OnCelestialBodyDataAssetChanged.Remove(CelestialBodyDataUpdateHandle);
	}
}
#endif
