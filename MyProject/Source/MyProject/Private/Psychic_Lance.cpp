// Fill out your copyright notice in the Description page of Project Settings.


#include "Psychic_Lance.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraSystem.h"
#include "PsychicCH.h"

// Sets default values
APsychic_Lance::APsychic_Lance()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SetRootComponent(Collider);
	Collider->InitSphereRadius(20.f);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &APsychic_Lance::OnOverlap);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
	StaticMesh->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

	MovementSpeed = 10000.f;
	TimeLived = 0.f;
	LifeSpan = 5.f;
}

// Called when the game starts or when spawned
void APsychic_Lance::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APsychic_Lance::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector NewLocation = GetActorLocation();
	NewLocation += GetActorForwardVector() * MovementSpeed * DeltaTime;
	SetActorLocation(NewLocation);

	TimeLived += DeltaTime;
	if (TimeLived > LifeSpan)
	{
		DestroyBullet();
	}
}

void APsychic_Lance::DestroyBullet()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	this->Destroy();
}

void APsychic_Lance::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<APsychicCH>())
	{
		Cast<APsychicCH>(OtherActor)->HitBy_PL();

		//Destroys bullet
		DestroyBullet();
	}
	

}