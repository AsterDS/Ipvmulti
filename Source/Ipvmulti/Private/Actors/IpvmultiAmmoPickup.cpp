#include "Actors/IpvmultiAmmoPickup.h"
#include "Components/BoxComponent.h"
#include "Ipvmulti/IpvmultiCharacter.h"

AIpvmultiAmmoPickup::AIpvmultiAmmoPickup()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	CollisionComponent->SetBoxExtent(FVector(50.f));
	CollisionComponent->SetCollisionProfileName("OverlapAllDynamic");
	RootComponent = CollisionComponent;
}

void AIpvmultiAmmoPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (!HasAuthority()) return;

	if (AIpvmultiCharacter* Player = Cast<AIpvmultiCharacter>(OtherActor))
	{
		Player->Server_RefillAmmo();
		Destroy();
	}
}

