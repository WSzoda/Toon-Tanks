// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"


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

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if(PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if(Subsystem){
			Subsystem->ClearAllMappings();
			Subsystem->AddMappingContext(InputMapping, 0);
			
			UEnhancedInputComponent* PEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

			PEnhancedInputComponent->BindAction(InputMoveForward, ETriggerEvent::Triggered, this, &ATank::Move);
			PEnhancedInputComponent->BindAction(InputLook, ETriggerEvent::Triggered, this, &ATank::Look);
			PEnhancedInputComponent->BindAction(InputShoot, ETriggerEvent::Triggered, this, &ATank::Shoot);
			PEnhancedInputComponent->BindAction(InputTurn, ETriggerEvent::Triggered, this, &ATank::Turn);
		}
	}
}

void ATank::Move(const FInputActionValue& Value)
{
	if(Controller)
	{
		const float MoveValue = Value.Get<float>();
		UE_LOG(LogTemp, Display, TEXT("working: %f"), MoveValue);
	}
}

void ATank::Turn(const FInputActionValue& Value)
{
}

void ATank::Shoot(const FInputActionValue& Value)
{
}

void ATank::Look(const FInputActionValue& Value)
{
}


