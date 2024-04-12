// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Navigation/PathFollowingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
    if (AIBehavior != nullptr)
    {
        RunBehaviorTree(AIBehavior);
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
    
}

void AShooterAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    
    // if (AIBehavior != nullptr)
    // {
    //     if (LineOfSightTo(PlayerPawn))
    //     {
    //         FVector PlayerLocation = PlayerPawn->GetActorLocation();
    //         GetBlackboardComponent()->SetValueAsVector("PlayerLocation", PlayerLocation);
    //         GetBlackboardComponent()->SetValueAsVector("LastKnownPlayerLocation", PlayerLocation);
    //     }
    //     else
    //     {
    //         GetBlackboardComponent()->ClearValue("PlayerLocation");
    //     }
    // }
}

bool AShooterAIController::IsCharacterDead() const
{
    AShooterCharacter* ControllerCharacter = Cast<AShooterCharacter>(GetPawn());
    if (ControllerCharacter != nullptr)
    {
        return ControllerCharacter->IsDead();
    }
    return true;
}
