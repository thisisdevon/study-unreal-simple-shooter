// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GunActor.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGunActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGunActor();

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent*  GunMesh;
	UPROPERTY(EditAnywhere)
	class UParticleSystem*  MuzzleFlashParticle;
	UPROPERTY(EditAnywhere)
	class UParticleSystem*  HitParticle;
	UPROPERTY(EditAnywhere)
	float MaxRange = 1000.f;
};
