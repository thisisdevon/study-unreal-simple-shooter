// Fill out your copyright notice in the Description page of Project Settings.


#include "GunActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet\GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AGunActor::AGunActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	GunMesh->SetupAttachment(Root);
}

void AGunActor::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlashParticle, GunMesh, "MuzzleFlashSocket");

	APawn* OwnerPawn = Cast<APawn>(GetOwner());

	if (OwnerPawn == nullptr)
	{
		return;
	}

	AController* OwnerController = OwnerPawn->GetController();

	if (OwnerController == nullptr)
	{
		return;
	}

	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector EndLocation = Location + Rotation.Vector() * MaxRange;
	FHitResult OutResult;
	if (GetWorld()->LineTraceSingleByChannel
	(
		OutResult,
		Location,
		EndLocation, 
		ECollisionChannel::ECC_GameTraceChannel1
	))
	{
		FVector ShotDirection = -Rotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, OutResult.Location, ShotDirection.Rotation());
	}
}

// Called when the game starts or when spawned
void AGunActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

