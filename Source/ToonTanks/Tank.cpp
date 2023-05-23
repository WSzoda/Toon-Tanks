// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerController = Cast<APlayerController>(GetController());
	if(PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if(Subsystem){
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(InputMapping, 0);
			
			UEnhancedInputComponent* PEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

			PEnhancedInputComponent->BindAction(InputMoveForward, ETriggerEvent::Triggered, this, &ATank::Move);
			PEnhancedInputComponent->BindAction(InputLook, ETriggerEvent::Triggered, this, &ATank::Look);
			PEnhancedInputComponent->BindAction(InputShoot, ETriggerEvent::Started, this, &ATank::Shoot);
			PEnhancedInputComponent->BindAction(InputTurn, ETriggerEvent::Triggered, this, &ATank::Turn);
		}
	}
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(PlayerController)
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		RotateTurret(HitResult.ImpactPoint);
	}
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::Move(const FInputActionValue& Value)
{
	if(Controller)
	{
		const float MoveValue = Value.Get<float>();
		FVector Forward = FVector::ZeroVector;
		Forward.X = MoveValue * MoveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
		AddActorLocalOffset(Forward, true);
	}
}

void ATank::Turn(const FInputActionValue& Value)
{
	if(Controller)
	{
		const float TurnValue = Value.Get<float>();
		FRotator Rotator = FRotator::ZeroRotator;
		Rotator.Yaw = TurnValue * RotateSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
		AddActorLocalRotation(Rotator, true);
	}
}

void ATank::Shoot(const FInputActionValue& Value)
{
	if(!Controller) return;
	
	if(Value.Get<bool>())
	{
		Fire();
	}
}

void ATank::Look(const FInputActionValue& Value)
{
}


