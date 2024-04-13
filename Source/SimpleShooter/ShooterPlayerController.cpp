// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::GameHasEnded(AActor * EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);
    UUserWidget* ResultScreen;
    if (bIsWinner)
    {
        ResultScreen = CreateWidget(this, WinScreenClass);
    }
    else
    {
        DeathFunction();
        ResultScreen = CreateWidget(this, LoseScreenClass);
    }
    if (ResultScreen != nullptr)
    {
        ResultScreen->AddToViewport();
    }
    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);

}

void AShooterPlayerController::RemoveHUDScreen()
{
    HUDScreen->RemoveFromParent();
}

void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();
    HUDScreen = CreateWidget(this, HUDScreenClass);
    HUDScreen->AddToViewport();
}


void AShooterPlayerController::DeathFunction()
{
    RemoveHUDScreen();
}
