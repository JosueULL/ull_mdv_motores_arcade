// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "LevelController.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "Enemy.h"
#include "MyGameStateBase.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
APlayerPawn::APlayerPawn() : 
	MovementSpeed(8),
	JumpForce(2000),
	GroundCheckLength(15)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject <UBoxComponent>("Root");
	Root->SetBoxExtent(FVector(16.f, 16.f, 16.f));
	Root->SetSimulatePhysics(true);
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject <UStaticMeshComponent>("BaseMeshComponent");
	Mesh->SetupAttachment(Root);
	
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	Root->OnComponentBeginOverlap.AddDynamic(this, &APlayerPawn::OnOverlapBegin);
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Right"), this, &APlayerPawn::OnMove);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &APlayerPawn::OnJump);
}

void APlayerPawn::OnMove(float value)
{
	// Move player horizontally
	FVector actorLocation = GetActorLocation();
	FVector disp = FVector::RightVector * value * MovementSpeed;
	SetActorLocation(actorLocation + disp);

	// Disable collision when player is going up
	FVector vel = Root->GetComponentVelocity();
	if (vel.Z > 0)
		Root->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Ignore);
	else
		Root->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Block);
	
	// Look slightly in the direction the player is going
	disp.Normalize();
	disp -= FVector::ForwardVector;
	FRotator rotation = FRotationMatrix::MakeFromX(-disp).Rotator();
	SetActorRotation(rotation);
}

void APlayerPawn::OnJump()
{
	FHitResult hit;
	FVector start = GetActorLocation() + GetActorUpVector();
	FVector end = start - GetActorUpVector() * GroundCheckLength;
	if (GetWorld()->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_WorldStatic) ||
		GetWorld()->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_WorldDynamic))
	{
		Root->AddImpulse(FVector(0, 0, JumpForce));

		if (ensure(JumpSound))
			UGameplayStatics::PlaySoundAtLocation(this, JumpSound, GetActorLocation());
	}
}

void APlayerPawn::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->ComponentHasTag(ALevelController::DeathTriggerTag) ||
		OtherComp->ComponentHasTag(AEnemy::EnemyTag)) {

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, OtherComp->GetFName().ToString());

		if (ensure(PFXDeath))
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), PFXDeath, GetActorTransform(), true);

		if (ensure(DeathSound))
			UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());

		AMyGameStateBase* state = Cast<AMyGameStateBase>(GetWorld()->GetGameState());
		state->EndGame();
	}
}
