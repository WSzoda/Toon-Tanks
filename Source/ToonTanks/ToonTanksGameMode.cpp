// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Turret.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
	if(DeadActor == PlayerTank)
	{
		PlayerTank->HandleDestruction();
		if(ToonTanksPlayerController)
		{
			ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if(ATurret* DestroyedTurret = Cast<ATurret>(DeadActor))
	{
		DestroyedTurret->HandleDestruction();
		TargetTowers--;
		if(TargetTowers == 0)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	HandleGameStart();
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
	TArray<AActor*> Turrets;
	UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(), Turrets);

	return Turrets.Num();
}

void AToonTanksGameMode::HandleGameStart()
{
	PlayerTank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	if(!PlayerTank) return;
	
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(PlayerTank->GetPlayerTankController());
	if(!ToonTanksPlayerController) return;

	StartGame();
	TargetTowers = GetTargetTowerCount();

	ToonTanksPlayerController->SetPlayerEnabledState(false);

	FTimerHandle PlayerEnableTimerHandle;
	FTimerDelegate PlayerEnableDelegate = FTimerDelegate::CreateUObject(
		ToonTanksPlayerController,
		&AToonTanksPlayerController::SetPlayerEnabledState,
		true
	);
	GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle,
		PlayerEnableDelegate,
		Delay,
		false
	);
}

