// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSection.h"
#include "Enemy.h"
#include "Components/BoxComponent.h"
#include "ActorUtils.h"

// Sets default values
ALevelSection::ALevelSection()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelSection::BeginPlay()
{
	Super::BeginPlay();

	//Create random content
	if (Content.Num() > 0) 
	{
		int32 index = FMath::RandRange(0, Content.Num() - 1);
		TSubclassOf<AActor> actor = Content[index];
		AActor* instance = GetWorld()->SpawnActor<AActor>(actor, GetActorLocation(), GetActorRotation(), FActorSpawnParameters());

		// Randomly disable some enemies
		TArray<AActor*> children;
		instance->GetAllChildActors(children);
		for (AActor* childActor : children) {
			if (childActor->IsA<AEnemy>())
			{
				if (FMath::FRand() > 0.5)
				{
					ActorUtils::Disable(childActor);
				}
			}
		}
	}

}

// Called every frame
void ALevelSection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
