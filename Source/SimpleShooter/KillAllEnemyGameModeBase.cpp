// Fill out your copyright notice in the Description page of Project Settings.


#include "KillAllEnemyGameModeBase.h"
#include "EngineUtils.h"
#include "ShooterAIController.h"
#include "GameFramework/Controller.h"

void AKillAllEnemyGameModeBase::PawnKilled(APawn *KilledPawn)
{
    Super::PawnKilled(KilledPawn);
    
    APlayerController* PlayerController = Cast<APlayerController>(KilledPawn->GetController());
    if (PlayerController != nullptr)
    {
        EndGame(false);
    }
    else
    {
        bool bIsEveryoneDead = true;
        for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
        {
            bIsEveryoneDead = bIsEveryoneDead == Controller->IsCharacterDead();
        }
        if (bIsEveryoneDead)
        {
            EndGame(true);
        }
    }
}

void AKillAllEnemyGameModeBase::EndGame(bool bIsPlayerWinner)
{
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        Controller->GameHasEnded(Controller->GetPawn(), Controller->IsPlayerController() == bIsPlayerWinner);
    }
}
