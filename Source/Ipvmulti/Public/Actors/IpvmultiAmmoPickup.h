#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IpvmultiAmmoPickup.generated.h"

UCLASS()
class IPVMULTI_API AIpvmultiAmmoPickup : public AActor
{
	GENERATED_BODY()
	
public:
	AIpvmultiAmmoPickup();

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UBoxComponent* CollisionComponent;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};


