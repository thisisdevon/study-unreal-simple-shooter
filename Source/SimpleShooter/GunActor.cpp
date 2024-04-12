// Fill out your copyright notice in the Description page of Project Settings.


#include "GunActor.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"
#include "Kismet/GameplayStatics.h"
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
	UGameplayStatics::SpawnSoundAttached(ShotSound, GunMesh, "MuzzleFlashSocket");

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

	FHitResult OutResult;
	FVector ShotDirection;
	if (GunTrace(OutResult, ShotDirection, OwnerController))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticle, OutResult.Location, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, OutResult.Location);
		
		AActor* HitActor = OutResult.GetActor();
		if (HitActor != nullptr)
		{

			FPointDamageEvent DamageEvent(DamageOnHit, OutResult, ShotDirection, nullptr);
			HitActor->TakeDamage(DamageOnHit, DamageEvent, OwnerController, this);
		}
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

bool AGunActor::GunTrace(FHitResult &HitRef, FVector &ShotDirection, AController *OwnerController)
{
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	ShotDirection = -Rotation.Vector();

	FVector EndLocation = Location + Rotation.Vector() * MaxRange;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
    return GetWorld()->LineTraceSingleByChannel
	(
		HitRef,
		Location,
		EndLocation, 
		ECollisionChannel::ECC_GameTraceChannel1,
		Params
	);
}
