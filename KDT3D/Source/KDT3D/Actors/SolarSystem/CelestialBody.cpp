#include "Actors/SolarSystem/CelestialBody.h"

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
		CelestialBodyDataUpdateHandle = CelestialBodyData->OnCelestialBodyDataAssetChanged.AddUObject(this, &ThisClass::OnCelestialBodyDataChanged);
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
		Cloud->AttachToComponent(RotatingAxis, FAttachmentTransformRules::KeepRelativeTransform);
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
}

// Called every frame
void ACelestialBody::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!CelestialBodyData) { return; }

	{
		const double Speed = CelestialBodyData->RotatingSpeed * DeltaTime;
		FRotator Rotator(0.0, Speed, 0.0);
		Body->AddRelativeRotation(Rotator);
	}
	if (Cloud)
	{
		const double Speed = CelestialBodyData->CloudRotatingSpeed * DeltaTime;
		FRotator Rotator(0.0, Speed, 0.0);
		Cloud->AddRelativeRotation(Rotator);
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
