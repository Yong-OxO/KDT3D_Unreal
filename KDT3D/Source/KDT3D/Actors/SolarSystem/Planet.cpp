// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SolarSystem/Planet.h"

void APlanet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (ACelestialBody* CelestialBody : Moons)
	{
		const double Speed = CelestialBody->GetOrbitalSpeed();
		FRotator Rotator(0.0, Speed, 0.0);
		CelestialBody->AddActorLocalRotation(Rotator);
	}
}

void APlanet::Destroyed()
{
	Super::Destroyed();

#if WITH_EDITOR
	if (GIsEditor && !FApp::IsGame())
	{
		for (ACelestialBody* CelestialBody : Moons)
		{
			if (CelestialBody) { CelestialBody->Destroy(); }				
		}
	}
#endif
}
#if WITH_EDITOR
void APlanet::PreEditChange(FProperty* PropertyAboutToChange)
{
	Super::PreEditChange(PropertyAboutToChange);

	const FString PropertyName = PropertyAboutToChange->GetName();
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, Moons))
	{
		PrevMoons = Moons;
	}
}

void APlanet::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FString PropertyName = PropertyChangedEvent.Property->GetName();
	if (PropertyName == GET_MEMBER_NAME_CHECKED(ThisClass, Moons))
	{
		const int32 Index = PropertyChangedEvent.GetArrayIndex(PropertyName);

		switch (PropertyChangedEvent.ChangeType)
		{
		case EPropertyChangeType::ArrayAdd:
		{
			Moons[Index] = AddMoon();
			break;
		}
		case EPropertyChangeType::ArrayRemove:
		{
			if (PrevMoons[Index])
			{
				// PrevMoons.RemoveAt(Index) Or PrevMoons[Index]->Destroy();
				// Edit환경이라 성능을 크게 중요시하지 않았을 수도 있다.
				ACelestialBody* PrevMoon = PrevMoons[Index];
				PrevMoon->Destroy();
			}
			break;
		}
		case EPropertyChangeType::Duplicate:
		{
			// 복제가 발생할 때 Moons의 Index자리에 공백이 생기고 그 자리에 복제된 객체가 들어간다.
			// -> 복제 된 객체가 마지막 Index를 차지하지 않는다. 복제 된 객체는 원본 객체의 Index를 차지하고 그 이후 객체들의 인덱스는 + 1
			if (PrevMoons[Index])
			{
				Moons[Index] = AddMoon(PrevMoons[Index]);
			}
			break;
		}
		case EPropertyChangeType::ArrayClear:
		{
			for (ACelestialBody* CelestialBody : PrevMoons)
			{
				CelestialBody->Destroy();
			}
			break;
		}
		default:
			check(nullptr);
			break;
		}

		PrevMoons.Empty();
	}


}
#endif

ACelestialBody* APlanet::AddMoon(ACelestialBody* InTemplate)
{
	UWorld* World = GetWorld();
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.Template = InTemplate;
	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	ActorSpawnParameters.TransformScaleMethod = ESpawnActorScaleMethod::OverrideRootScale;

	const FTransform NewTransform = InTemplate ? InTemplate->GetTransform() : GetTransform();
	ACelestialBody* CelestialBody = World->SpawnActor<ACelestialBody>(ACelestialBody::StaticClass(), NewTransform, ActorSpawnParameters);

	if (CelestialBody)
	{
		CelestialBody->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	}

	return CelestialBody;
}
