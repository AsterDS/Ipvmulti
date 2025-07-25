// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/ObjectiveActor.h"

#include "Components/SphereComponent.h"
#include "Ipvmulti/IpvmultiCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AObjectiveActor::AObjectiveActor()
{
	bReplicates = true;
	
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionResponseToChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	SphereComp->SetupAttachment(RootComponent);
}

void AObjectiveActor::BeginPlay()
{
	Super::BeginPlay();

}

void AObjectiveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AObjectiveActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	PlayEffects();

	AIpvmultiCharacter* myCharacter = Cast<AIpvmultiCharacter>(OtherActor);

	if (myCharacter)
	{
		myCharacter->bIsCarryingObjective = true;
		Destroy();
	}
}

void AObjectiveActor::PlayEffects()
{
	UGameplayStatics::SpawnEmitterAtLocation(this,PickupVFX,GetActorLocation());
}