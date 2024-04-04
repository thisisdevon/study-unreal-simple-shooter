// Fill out your copyright notice in the Description page of Project Settings.


#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "ShooterCharacter.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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
	PEI->BindAction(InputJump, ETriggerEvent::Triggered, this, &AShooterCharacter::JumpOnTheSpot);
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

void AShooterCharacter::JumpOnTheSpot(const FInputActionValue &Value)
{
	Jump();
}
