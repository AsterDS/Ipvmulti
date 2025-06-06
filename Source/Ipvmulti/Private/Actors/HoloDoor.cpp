#include "Actors/HoloDoor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"

AHoloDoor::AHoloDoor()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);

	bIsOpen = false;
}

void AHoloDoor::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetDoorPassable(false);
		GetWorldTimerManager().SetTimer(ToggleTimerHandle, this, &AHoloDoor::ToggleDoor, 2.0f, true);
	}
	else
	{
		SetDoorPassable(bIsOpen);
	}
}

void AHoloDoor::ToggleDoor()
{
	if (!HasAuthority())
	{
		ServerToggleDoor();
		return;
	}

	const bool bNewState = !bIsOpen;
	SetDoorPassable(bNewState);

	if (bNewState && SecondDoor)
	{
		SecondDoor->SetDoorPassable(false);
	}
}

void AHoloDoor::ServerToggleDoor_Implementation()
{
	ToggleDoor();
}

void AHoloDoor::SetDoorPassable(bool bPassable)
{
	bIsOpen = bPassable;

	if (bPassable)
	{
		if (PassableMaterial)
		{
			DoorMesh->SetMaterial(0, PassableMaterial);
		}
		DoorMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
	{
		if (SolidMaterial)
		{
			DoorMesh->SetMaterial(0, SolidMaterial);
		}
		DoorMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void AHoloDoor::OnRep_IsOpen()
{
	SetDoorPassable(bIsOpen);
}

void AHoloDoor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AHoloDoor, bIsOpen);
}

