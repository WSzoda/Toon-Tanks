// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Turret.generated.h"
class ATank;

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATurret : public ABasePawn
{
	GENERATED_BODY()
	
public:
	ATurret();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category="Combat")
	float MaxDistance = 500;

	UPROPERTY(EditAnywhere, Category="Combat")
	float FireRate = 2.f;
	
	ATank* PlayersTank;

	FTimerHandle FireRateTimerHandle;
	
	void AimAtPlayer();
	
	void CheckFireCondition();

	bool IsInFireRange() const;

	void Shoot();
};
