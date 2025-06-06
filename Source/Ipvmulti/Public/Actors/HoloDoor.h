#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HoloDoor.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class IPVMULTI_API AHoloDoor : public AActor
{
	GENERATED_BODY()
    
public:
	AHoloDoor();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void ToggleDoor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HoloDoor")
	AHoloDoor* SecondDoor;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnRep_IsOpen();

	UPROPERTY(ReplicatedUsing = OnRep_IsOpen)
	bool bIsOpen;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;

private:
	void SetDoorPassable(bool bPassable);

	UFUNCTION(Server, Reliable)
	void ServerToggleDoor();

	UPROPERTY(EditAnywhere, Category = "HoloDoor")
	UMaterialInterface* PassableMaterial;

	UPROPERTY(EditAnywhere, Category = "HoloDoor")
	UMaterialInterface* SolidMaterial;

	FTimerHandle ToggleTimerHandle;
};



