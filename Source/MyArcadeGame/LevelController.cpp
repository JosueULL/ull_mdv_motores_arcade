// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelController.h"
#include "LevelSection.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

const FName ALevelController::DeathTriggerTag = FName("DeathTriggerTag");

// Sets default values
ALevelController::ALevelController() : SectionGap(100)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	NewSectionTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("NewInstanceTrigger"));
	NewSectionTrigger->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	
	NewSectionTrigger->SetBoxExtent(FVector(32, 300, 50));
	NewSectionTrigger->SetupAttachment(Root);

	DeathTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("DeathTrigger"));
	DeathTrigger->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	
	DeathTrigger->SetBoxExtent(FVector(32, 300, 50));
	DeathTrigger->SetupAttachment(Root);
	DeathTrigger->ComponentTags.Add(DeathTriggerTag);
}

void ALevelController::BeginPlay()
{
	Super::BeginPlay();

	NewSectionTrigger->OnComponentBeginOverlap.AddDynamic(this, &ALevelController::OnOverlapNewSectionBegin);
	
	APlayerController* playerCtrl = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerActor = playerCtrl->GetPawn();

	if (ensureAlways(MainCamera))
		playerCtrl->SetViewTarget(MainCamera);
}

// Called every frame
void ALevelController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ensure(MainCamera))
	{
		// Match camera Z position with player's
		FVector playerWorldLocation = PlayerActor->GetActorLocation();
		FVector camWorldLocation = MainCamera->GetActorLocation();
		float newZ = playerWorldLocation.Z + 10;

		float const camMovThreshold = 0.1f;
		if (newZ > camWorldLocation.Z && abs(newZ - camWorldLocation.Z) > camMovThreshold)
			MainCamera->SetActorLocation(FVector(camWorldLocation.X, 0, newZ));
	}
}

void ALevelController::OnOverlapNewSectionBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!(OtherActor == PlayerActor))
		return;
	

	FVector newLocation = NewSectionTrigger->GetRelativeLocation() + GetActorUpVector() * SectionGap;
	NewSectionTrigger->SetRelativeLocation(newLocation);

	newLocation += GetActorUpVector() * InstancingOffset;
	GetWorld()->SpawnActor(Section.Get(), &newLocation);
	
	FVector newDeathLocation = DeathTrigger->GetRelativeLocation() + GetActorUpVector() * SectionGap;
	DeathTrigger->SetRelativeLocation(newDeathLocation);
}
