// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"
class UHealthComponent;
class UCapsuleComponent;
class AProjectile;
class USoundBase;

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Pawn Components")
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Pawn Components")
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Pawn Components")
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Pawn Components")
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	UParticleSystem* DeathParticle;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category="Combat")
	TSubclassOf<UCameraShakeBase> DeathCameraShake;
	
	
	void RotateTurret(FVector LookAtTarget);

	void Fire();

	void virtual HandleDestruction();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
