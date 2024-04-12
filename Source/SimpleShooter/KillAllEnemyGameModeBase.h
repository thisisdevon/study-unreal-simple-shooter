// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooterGameModeBase.h"
#include "KillAllEnemyGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AKillAllEnemyGameModeBase : public ASimpleShooterGameModeBase
{
	GENERATED_BODY()
public:
	virtual void PawnKilled(APawn *KilledPawn) override;
};
