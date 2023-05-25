// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

class AToonTanksPlayerController;
class ATank;
/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* DeadActor);

protected:
	virtual void BeginPlay() override;

private:
	ATank* PlayerTank;
	AToonTanksPlayerController* ToonTanksPlayerController;

	float Delay = 3.f;

	int32 TargetTowers = 0;
	int32 GetTargetTowerCount();

	void HandleGameStart();

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);
};
