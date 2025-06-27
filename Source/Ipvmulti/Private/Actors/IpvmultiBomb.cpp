#include "Actors/IpvmultiBomb.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

AIpvmultiBomb::AIpvmultiBomb()
{
    bReplicates = true;

    CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    CollisionComp->InitSphereRadius(100.f);
    CollisionComp->SetCollisionProfileName("Trigger");
    RootComponent = CollisionComp;

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetupAttachment(RootComponent);

    CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AIpvmultiBomb::OnOverlapBegin);

    bIsActive = true;

    static ConstructorHelpers::FObjectFinder<UParticleSystem> DefaultExplosionEffect(TEXT("/Game/StarterContent/Particles/P_Explosion.P_Explosion"));
    if (DefaultExplosionEffect.Succeeded())
    {
        ExplosionEffect = DefaultExplosionEffect.Object;
    }
}

void AIpvmultiBomb::BeginPlay()
{
    Super::BeginPlay();
}

void AIpvmultiBomb::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                   bool bFromSweep, const FHitResult& SweepResult)
{
    if (!HasAuthority() || !bIsActive) return;

    ACharacter* Player = Cast<ACharacter>(OtherActor);
    if (Player)
    {
        UGameplayStatics::ApplyDamage(Player, Damage, nullptr, this, nullptr);

        Multicast_PlayExplosionEffect(GetActorLocation());
        
        SetBombActive(false);
        GetWorldTimerManager().SetTimer(TimerHandle_Reactivation, this, &AIpvmultiBomb::ReactivateBomb, 5.0f, false);
    }
}

void AIpvmultiBomb::SetBombActive(bool bActive)
{
    bIsActive = bActive;
    
    SetActorHiddenInGame(!bActive);
    SetActorEnableCollision(bActive);
    
    Multicast_SetBombActive(bActive);
}

void AIpvmultiBomb::Multicast_SetBombActive_Implementation(bool bActive)
{
    bIsActive = bActive;
    SetActorHiddenInGame(!bActive);
    SetActorEnableCollision(bActive);
}

void AIpvmultiBomb::ReactivateBomb()
{
    SetBombActive(true);
}

void AIpvmultiBomb::Multicast_PlayExplosionEffect_Implementation(FVector Location)
{
    if (ExplosionEffect)
    {
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionEffect, Location);
    }
}

void AIpvmultiBomb::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AIpvmultiBomb, bIsActive);
}


