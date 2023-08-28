// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Psychic_Lance.generated.h"


class USphereComponent;

UCLASS()
class MYPROJECT_API APsychic_Lance : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APsychic_Lance();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USphereComponent* Collider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* StaticMesh;

	/** Public Variables */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		float LifeSpan;
	UFUNCTION()
		void DestroyBullet();

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);
private:
	/** Private Variables */

	float TimeLived;

};
