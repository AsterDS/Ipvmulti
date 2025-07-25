#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectiveActor.generated.h"

class USphereComponent;
class UParticleSystem;

UCLASS()
class IPVMULTI_API AObjectiveActor : public AActor
{
	GENERATED_BODY()

public:
	AObjectiveActor();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere,Category="Components")
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere,Category="Components")
	USphereComponent* SphereComp;

	UPROPERTY(EditDefaultsOnly,Category="VFX")
	UParticleSystem* PickupVFX;

	void PlayEffects();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};