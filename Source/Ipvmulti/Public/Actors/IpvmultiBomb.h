#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IpvmultiBomb.generated.h"

UCLASS()
class IPVMULTI_API AIpvmultiBomb : public AActor
{
	GENERATED_BODY()

public:
	AIpvmultiBomb();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
						bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void ReactivateBomb();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SetBombActive(bool bActive);

	void SetBombActive(bool bActive);

	FTimerHandle TimerHandle_Reactivation;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(EditAnywhere, Category = "Effects")
	class UParticleSystem* ExplosionEffect;

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_PlayExplosionEffect(FVector Location);
	
	UPROPERTY(EditAnywhere, Category = "Bomb")
	float Damage = 40.f;

	UPROPERTY(Replicated)
	bool bIsActive;

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};

