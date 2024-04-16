// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "InputAction.h"
#include "GunActor.h"
#include "Components/CapsuleComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "SimpleShooterGameModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Health = MaxHealth;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	for (int i = 0; i < GunClassArray.Num(); i++)
	{
		AGunActor* SpawnedGun = GetWorld()->SpawnActor<AGunActor>(GunClassArray[i]);
		GunArray.Add(SpawnedGun);
		if (i == GunActiveIndex)
		{
			SpawnedGun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "WeaponSocket");
			SpawnedGun->SetOwner(this);
		}
		else
		{
			HideGun(i);
		}
	}
}

bool AShooterCharacter::IsDead() const
{
    return Health <= 0.f;
}

float AShooterCharacter::GetHealthPercentage() const
{
	return Health / MaxHealth;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
    // Get the local player subsystem
    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
    // Clear out existing mapping, and add our mapping
    Subsystem->ClearAllMappings();
    Subsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* PEI = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	PEI->BindAction(InputMoveForward, ETriggerEvent::Triggered, this, &AShooterCharacter::MoveForward);
	PEI->BindAction(InputLookUp, ETriggerEvent::Triggered, this, &AShooterCharacter::LookUp);
	PEI->BindAction(InputLookUpRate, ETriggerEvent::Triggered, this, &AShooterCharacter::LookUpRate);
	PEI->BindAction(InputJump, ETriggerEvent::Triggered, this, &AShooterCharacter::JumpOnTheSpot);
	PEI->BindAction(InputShootGun, ETriggerEvent::Triggered, this, &AShooterCharacter::ShootGun);
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	Health = FMath::Max(0.f, Health - DamageApplied);
	UE_LOG(LogTemp, Display, TEXT("Health remaing: %f"), Health);

	if (IsDead())
	{
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
    return DamageApplied;
}

void AShooterCharacter::MoveForward(const FInputActionValue& Value)
{
	const FVector2D MoveValue = Value.Get<FVector2D>();
	// Forward/Backward direction
	if (MoveValue.Y != 0.f)
	{
		AddMovementInput(GetActorForwardVector(), MoveValue.Y);
	}
	// Right/Left direction
	if (MoveValue.X != 0.f)
	{
		AddMovementInput(GetActorRightVector(), MoveValue.X);
	}
}

void AShooterCharacter::LookUp(const FInputActionValue &Value)
{
	const FVector2D MoveValue = Value.Get<FVector2D>();
	
	// Forward/Backward direction
	if (MoveValue.Y != 0.f)
	{
		AddControllerPitchInput(MoveValue.Y);
	}
	// Right/Left direction
	if (MoveValue.X != 0.f)
	{
		AddControllerYawInput(-MoveValue.X);
	}
}

void AShooterCharacter::LookUpRate(const FInputActionValue &Value)
{
	const FVector2D MoveValue = Value.Get<FVector2D>();
	
	// Forward/Backward direction
	if (MoveValue.Y != 0.f)
	{
		AddControllerPitchInput(MoveValue.Y * RotationRate);
	}
	// Right/Left direction
	if (MoveValue.X != 0.f)
	{
		AddControllerYawInput(MoveValue.X * RotationRate);
	}
}

void AShooterCharacter::JumpOnTheSpot(const FInputActionValue &Value)
{
	Jump();
}

void AShooterCharacter::ShootGun(const FInputActionValue& Value)
{
	GetActiveGun()->PullTrigger();
}

AGunActor * AShooterCharacter::GetActiveGun()
{
	return GunArray[GunActiveIndex];
}

void AShooterCharacter::HideGun(int32 HiddenGunIndex)
{
	GunArray[HiddenGunIndex]->SetActorHiddenInGame(true);
}

void AShooterCharacter::ShowGun(int32 ShownGunIndex)
{
	GunArray[ShownGunIndex]->SetActorHiddenInGame(false);
}
