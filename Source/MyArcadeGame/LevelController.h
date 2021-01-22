// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelController.generated.h"


UCLASS()
class MYARCADEGAME_API ALevelController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALevelController();

private:
	UPROPERTY(EditAnywhere)
		AActor* PlayerActor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapNewSectionBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		class USceneComponent* Root;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* NewSectionTrigger;

	UPROPERTY(EditAnywhere)
		class UBoxComponent* DeathTrigger;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class ALevelSection> Section;

	UPROPERTY(EditAnywhere)
		AActor* MainCamera;

	UPROPERTY(EditAnywhere)
		float SectionGap;

	UPROPERTY(EditAnywhere)
		float InstancingOffset;

	static const FName DeathTriggerTag;


};
