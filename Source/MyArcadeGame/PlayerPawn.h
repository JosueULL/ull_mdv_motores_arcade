// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class MYARCADEGAME_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public: 

	UPROPERTY(EditAnywhere)
	float MovementSpeed;
	
	UPROPERTY(EditAnywhere)
	float JumpForce;

	UPROPERTY(EditAnywhere)
		float GroundCheckLength;

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

	void OnMove(float value);

	void OnJump();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UBoxComponent* Root;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UStaticMeshComponent* Mesh;

	//UPROPERTY(BlueprintReadOnly, EditAnywhere)
		//class UCameraComponent* Camera;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class UBoxComponent* Collision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UParticleSystem * PFXDeath;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class USoundBase* JumpSound;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
		class USoundBase* DeathSound;
};
