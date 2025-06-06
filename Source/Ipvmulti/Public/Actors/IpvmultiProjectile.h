#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IpvmultiProjectile.generated.h"

UCLASS()
class IPVMULTI_API AIpvmultiProjectile : public AActor
{
	GENERATED_BODY()

protected:
	virtual void Destroyed() override;

	UFUNCTION(Category="Projectile")
	void OnProjectileImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	
	AIpvmultiProjectile();
	
	// Sphere component used to test collision.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	class USphereComponent* SphereComponent;
 
	// Static Mesh used to provide a visual representation of the object.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	class UStaticMeshComponent* StaticMesh;
 
	// Movement component for handling projectile movement.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	class UProjectileMovementComponent* ProjectileMovementComponent;
 
	// Particle used when the projectile impacts against another object and explodes.
	UPROPERTY(EditAnywhere, Category = "Effects")
	class UParticleSystem* ExplosionEffect;
 
	//The damage type and damage that will be done by this projectile
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Damage")
	TSubclassOf<class UDamageType> DamageType;
 
	//The damage dealt by this projectile.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Damage")
	float Damage;
};
