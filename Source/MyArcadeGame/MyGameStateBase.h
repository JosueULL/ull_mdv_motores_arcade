// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDynamicMulticast);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDynamicMulticastOneParam, float, Score);

/**
 * 
 */
UCLASS()
class MYARCADEGAME_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	AMyGameStateBase();

private:
	

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		int Score;

	UFUNCTION()
		void EndGame();

	UPROPERTY(BlueprintAssignable)
		FDynamicMulticast OnGameOver;

	UPROPERTY(BlueprintAssignable)
		FDynamicMulticastOneParam OnScoreChanged;

};
