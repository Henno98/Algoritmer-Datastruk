// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PsychicCH.generated.h"


struct FInputActionValue;

class UInputAction;
class UNiagaraSystem;
class UNiagaraComponent;
class APsychic_Lance;
class APsychic_Blast;

UCLASS()
class MYPROJECT_API APsychicCH : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APsychicCH();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
		class USpringArmComponent* SpringArm{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerVariables")
		class UCameraComponent* Camera{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		TSubclassOf<APsychic_Lance> BP_Psychic_Lance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
		TSubclassOf<APsychic_Blast> BP_Psychic_Blast;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	int Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float CurrentHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	int Stamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float CurrentStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	int Energy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float CurrentEnergy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int StatTotal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int Strength = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int Endurance = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int Intelligence = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int Wisdom = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int Mystic = 100;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float ResistPercentage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float EnergyRegen;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float HealthRegen = 2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float StaminaRegen = 5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float PhysicaRes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float MentalRes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float MagicRes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Variables")
	float Timer;
	
	void DamageCalc();
	
	void DefenseCalc();
	
	void HealthCalc();
	
	void StaminaCalc();
	
	void EnergyCalc();
	
	void RegenCalc();
	
	void PsychicBlast();
	
	void PsychicSpear();
	
	void Dash();
	
	void HitBy_PB();
	
	void HitBy_PL();

	bool Dashing;
	//float setup
	float XInput;
	float YInput;
	float Yaw;
	float Roll;
	float Pitch;

	//Input Mapping setup
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		class UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		UInputAction* ForwardInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		UInputAction* UpInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		UInputAction* RightInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		UInputAction* PsychicBlastInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		UInputAction* PsychicLanceInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		UInputAction* MouseXInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		UInputAction* MouseYInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		UInputAction* DashInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		UInputAction* SettingsInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		UInputMappingContext* Player2_MC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		UInputAction* ForwardInput2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		UInputAction* UpInput2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = InputSystem)
		UInputAction* RightInput2;

	void Forward(const FInputActionValue& input);
	void Right(const FInputActionValue& input);
	void MouseX(const FInputActionValue& input);
	void MouseY(const FInputActionValue& input);

	void Movement();

	FVector3d ActorLocation;
	FVector3d NewSpawnLocation;
};
