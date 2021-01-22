// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"

UCLASS()
class MYARCADEGAME_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	enum EDirection {
		EDir_Start,
		EDir_End
	};

	EDirection Dir;

	FVector StartPos;
	FVector EndPos;

	float CurrentT;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Start;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float End;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* Root;

	static const FName EnemyTag;
};
