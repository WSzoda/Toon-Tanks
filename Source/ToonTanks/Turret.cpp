// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ATurret::ATurret()
{
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimAtPlayer();
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();

	PlayersTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	GetWorldTimerManager().SetTimer(
		FireRateTimerHandle,
		this,
		&ATurret::CheckFireCondition,
		FireRate,
		true
		);
}

void ATurret::AimAtPlayer()
{
	if(!PlayersTank) return;
	
	float const Distance = FVector::Dist(GetActorLocation(), PlayersTank->GetActorLocation());
	if(Distance > MaxDistance) return;

	RotateTurret(PlayersTank->GetActorLocation());
}

void ATurret::CheckFireCondition()
{
	if(!PlayersTank) return;
	if(!IsInFireRange()) return;
	if(!PlayersTank->bAlive) return;

	Shoot();
}

void ATurret::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

bool ATurret::IsInFireRange() const
{
	if(!PlayersTank) return false;
	
	float const Distance = FVector::Dist(GetActorLocation(), PlayersTank->GetActorLocation());
	if(Distance > MaxDistance)
	{
		return false;
	}
	return true;
}

void ATurret::Shoot()
{
	if(!PlayersTank) return;

	Fire();
	DrawDebugSphere(
		GetWorld(),
		ProjectileSpawnPoint->GetComponentLocation(),
		10.f,
		10,
		FColor::Red,
		false,
		3.f
		);
}
