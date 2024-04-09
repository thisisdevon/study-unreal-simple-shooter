// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    
}

void AShooterAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    
    if (LineOfSightTo(PlayerPawn))
    {
        if (GetMoveStatus() != EPathFollowingStatus::Moving)
        {
            MoveToActor(PlayerPawn, AcceptanceByRadius, true);
        }
        SetFocus(PlayerPawn, EAIFocusPriority::Gameplay);
    }
    else
    {
        ClearFocus(EAIFocusPriority::Gameplay);
        StopMovement();
    }
}
