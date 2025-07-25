#include "Game/IpvmultiGameState.h"
#include "EngineUtils.h"
#include "Player/IpvmultiPlayerController.h"

void AIpvmultiGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bMissionSuccess)
{
	/*
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
		if (APawn* Pawn = PC->GetPawn())
			Pawn->DisableInput(nullptr);
			*/

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		AIpvmultiPlayerController* PC = Cast<AIpvmultiPlayerController>(It->Get());
		if (PC)
		{
			PC->OnMissionCompleted(InstigatorPawn, bMissionSuccess);
			APawn* Pawn = PC->GetPawn();
			if (Pawn)
			{
				Pawn->DisableInput(nullptr);
			}
		}
	}
}
