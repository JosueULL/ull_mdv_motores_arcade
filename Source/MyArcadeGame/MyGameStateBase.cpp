// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "ActorUtils.h"


AMyGameStateBase::AMyGameStateBase() 
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AMyGameStateBase::EndGame() 
{
	APlayerController* playerCtrl = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	AActor* playerActor = playerCtrl->GetPawn();

	ActorUtils::Disable(playerActor);

	OnGameOver.Broadcast();
}

void AMyGameStateBase::Tick(float DeltaTime) 
{
	APawn* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	int currentScore = player->GetActorLocation().Z;
	if (currentScore > Score)
	{
		Score = currentScore;
		OnScoreChanged.Broadcast(Score);
	}
}
