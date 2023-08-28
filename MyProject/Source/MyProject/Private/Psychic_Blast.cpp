// Fill out your copyright notice in the Description page of Project Settings.


#include "Psychic_Blast.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraSystem.h"
#include "PsychicCH.h"

// Sets default values
APsychic_Blast::APsychic_Blast()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->InitBoxExtent(FVector(10.f, 10.f, 10.f));
	Collider->OnComponentBeginOverlap.AddDynamic(this, &APsychic_Blast::OnOverlap);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	StaticMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	MovementSpeed = 1000.f;
	TimeLived = 0.f;
	LifeSpan = 0.5f;
}

// Called when the game starts or when spawned
void APsychic_Blast::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APsychic_Blast::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	
	SetActorLocation(NewLocation);

	TimeLived += DeltaTime;
	if (TimeLived > LifeSpan)
	{
		DestroyBullet();
	}
}

void APsychic_Blast::DestroyBullet()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	this->Destroy();
}

void APsychic_Blast::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<APsychicCH>())
	{
		Cast<APsychicCH>(OtherActor)->HitBy_PB();

		//Destroys bullet
		DestroyBullet();
	}
}

