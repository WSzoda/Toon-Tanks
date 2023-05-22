// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "Tank.h"
#include "Kismet/GameplayStatics.h"

ATurret::ATurret()
{
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();

	PlayersTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 9));
}

void ATurret::AimAtPlayer()
{
	if(!PlayersTank) return;
	
	float const Distance = FVector::Dist(GetActorLocation(), PlayersTank->GetActorLocation());
	if(Distance > MaxDistance) return;

	RotateTurret(PlayersTank->GetActorLocation());
}
