// Fill out your copyright notice in the Description page of Project Settings.


#include "KillAllEnemyGameModeBase.h"

void AKillAllEnemyGameModeBase::PawnKilled(APawn *KilledPawn)
{
    Super::PawnKilled(KilledPawn);
    
    APlayerController* PlayerController = Cast<APlayerController>(KilledPawn->GetController());
    if (PlayerController != nullptr)
    {
        PlayerController->GameHasEnded(nullptr, false);
    }
}
