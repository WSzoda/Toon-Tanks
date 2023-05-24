// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Tank.h"
#include "Turret.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if(DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		if(PlayerTank->GetPlayerTankController())
		{
			PlayerTank->DisableInput(PlayerTank->GetPlayerTankController());
			PlayerTank->GetPlayerTankController()->bShowMouseCursor = false;
		}
	}
	else if(ATurret* DestroyedTurret = Cast<ATurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
}
