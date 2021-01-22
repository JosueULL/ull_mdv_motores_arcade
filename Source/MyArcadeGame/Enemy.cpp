// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Math/UnrealMathUtility.h"


const FName AEnemy::EnemyTag = FName("Enemy");

// Sets default values
AEnemy::AEnemy()
{
	Start = 50;
	End = -50;
	Speed = 15;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject <UBoxComponent>(TEXT("Root"));
	Root->ComponentTags.Add(EnemyTag);
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
	Mesh->SetupAttachment(Root);
	Mesh->SetEnableGravity(false);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	StartPos = GetActorLocation() + GetActorRightVector() * Start;
	EndPos = GetActorLocation() + GetActorRightVector() * End;

	CurrentT = FMath::FRand();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float length = FVector::Distance(StartPos, EndPos);
	FVector pointA = (Dir == EDirection::EDir_Start ? StartPos : EndPos);
	FVector pointB = (Dir == EDirection::EDir_Start ? EndPos : StartPos);
	CurrentT += (Speed / length) * DeltaTime;

	FVector newLocation = FMath::Lerp(pointA, pointB, CurrentT);
	SetActorLocation(newLocation);

	if (CurrentT > 1 || CurrentT < 0) 
	{
		Dir = (Dir == EDirection::EDir_Start ? EDirection::EDir_End : EDirection::EDir_Start);
		CurrentT = 0;
	}
	
}

