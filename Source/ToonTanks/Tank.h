// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "InputActionValue.h"
#include "Tank.generated.h"
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
public:
	ATank();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditDefaultsOnly, Category="Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	UCameraComponent* Camera;

	APlayerController* PlayerController;

protected:
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	UInputMappingContext* InputMapping;

	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	UInputAction* InputMoveForward;

	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	UInputAction* InputTurn;

	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	UInputAction* InputShoot;

	UPROPERTY(EditDefaultsOnly, Category = "Enhanced Input")
	UInputAction* InputLook;

	void Move(const FInputActionValue& Value);

	void Turn(const FInputActionValue& Value);

	void Shoot(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed = 50;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotateSpeed = 50;
};
