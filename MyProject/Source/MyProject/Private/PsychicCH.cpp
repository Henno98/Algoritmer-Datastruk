// Fill out your copyright notice in the Description page of Project Settings.


#include "PsychicCH.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Psychic_Lance.h"
#include "Psychic_Blast.h"
#include "GameFramework/PlayerState.h"


// Sets default values
APsychicCH::APsychicCH()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Springarm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 400.f; // Distance from player
	SpringArm->bUsePawnControlRotation = true; // Rotate arm based on controller
	//Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = true;

	Timer = 30.f;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	Dashing = false;
}

// Called when the game starts or when spawned
void APsychicCH::BeginPlay()
{
	Super::BeginPlay();
	
	//Controller Setup
	if (UGameplayStatics::GetPlayerController(this, 0) != nullptr) 
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);;
		if (PlayerController)
		{
			UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
			if (subsystem)
			{
				subsystem->AddMappingContext(MappingContext, 0);
			}
		}
	}
	else if(UGameplayStatics::GetPlayerController(this, 1) != nullptr)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 1);;
		if (PlayerController)
		{
			UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
			if (subsystem)
			{
				subsystem->AddMappingContext(Player2_MC, 0);
			}
		}
	}
	EnergyCalc();
	HealthCalc();
	StaminaCalc();
	StatTotal = (Strength + Wisdom + Intelligence + Endurance + Mystic);
}

// Called every frame
void APsychicCH::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentStamina > 0) 
	{
		Movement();
	}

	if (CurrentHealth <= 0) {
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
	}
	RegenCalc();

	if(Dashing == true)
	{
		GetCharacterMovement()->MaxAcceleration = 100000;
	}
	else
	{
		GetCharacterMovement()->MaxAcceleration = 5000;
	}
	AddControllerYawInput(Yaw);
	AddControllerPitchInput(Pitch);
}

// Called to bind functionality to input
void APsychicCH::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	APlayerController* PC = Cast<APlayerController>(GetController());

	if (UEnhancedInputComponent* EnhanceInputCom = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhanceInputCom->BindAction(ForwardInput, ETriggerEvent::Triggered, this, &APsychicCH::Forward);
		EnhanceInputCom->BindAction(RightInput, ETriggerEvent::Triggered, this, &APsychicCH::Right);
		EnhanceInputCom->BindAction(ForwardInput, ETriggerEvent::Completed, this, &APsychicCH::Forward);
		EnhanceInputCom->BindAction(RightInput, ETriggerEvent::Completed, this, &APsychicCH::Right);

		EnhanceInputCom->BindAction(DashInput, ETriggerEvent::Triggered, this, &APsychicCH::Dash);
		

		EnhanceInputCom->BindAction(MouseXInput, ETriggerEvent::Started, this, &APsychicCH::MouseX);
		EnhanceInputCom->BindAction(MouseYInput, ETriggerEvent::Started, this, &APsychicCH::MouseY);
		EnhanceInputCom->BindAction(MouseXInput, ETriggerEvent::Triggered, this, &APsychicCH::MouseX);
		EnhanceInputCom->BindAction(MouseYInput, ETriggerEvent::Triggered, this, &APsychicCH::MouseY);
		EnhanceInputCom->BindAction(MouseXInput, ETriggerEvent::Completed, this, &APsychicCH::MouseX);
		EnhanceInputCom->BindAction(MouseYInput, ETriggerEvent::Completed, this, &APsychicCH::MouseY);

		EnhanceInputCom->BindAction(PsychicBlastInput, ETriggerEvent::Triggered, this, &APsychicCH::PsychicBlast);
		EnhanceInputCom->BindAction(PsychicBlastInput, ETriggerEvent::Completed, this, &APsychicCH::PsychicBlast);
		EnhanceInputCom->BindAction(PsychicLanceInput, ETriggerEvent::Completed, this, &APsychicCH::PsychicSpear);

		EnhanceInputCom->BindAction(ForwardInput2, ETriggerEvent::Triggered, this, &APsychicCH::Forward);
		EnhanceInputCom->BindAction(RightInput2, ETriggerEvent::Triggered, this, &APsychicCH::Right);
		EnhanceInputCom->BindAction(ForwardInput2, ETriggerEvent::Completed, this, &APsychicCH::Forward);
		EnhanceInputCom->BindAction(RightInput2, ETriggerEvent::Completed, this, &APsychicCH::Right);
	}
}

void APsychicCH::Forward(const FInputActionValue& input)
{
	XInput = input.Get<float>();
}

void APsychicCH::Right(const FInputActionValue& input)
{
	YInput = input.Get<float>();
}

void APsychicCH::MouseX(const FInputActionValue& input)
{
	Yaw = input.Get<float>();
}

void APsychicCH::MouseY(const FInputActionValue& input)
{
	Pitch = input.Get<float>();
}

void APsychicCH::Movement()
{
	
	//Movement
	if (GetController() != nullptr) {
		FRotator ControlRotation = GetController()->GetControlRotation();


		ControlRotation.Roll = 0.f;
		ControlRotation.Pitch = 0.f;
		/*ControlRotation.Yaw = 0.f;*/

		//Getting the direction we're looking, and the right vector = cross product of forward and up vectors
		FVector ForwardVector = UKismetMathLibrary::GetForwardVector(ControlRotation);
		FVector RightVector = UKismetMathLibrary::GetRightVector(ControlRotation);

		ForwardVector *= XInput;
		RightVector *= YInput;

		if (!FMath::IsNearlyZero(XInput))
		{
			AddMovementInput(ForwardVector);

			if (Dashing) {
				CurrentStamina -= 5;
			}
			else {
				CurrentStamina -= 1;
			}
		}
		if (!FMath::IsNearlyZero(YInput))
		{
			AddMovementInput(RightVector);
			if (Dashing) {
				CurrentStamina -= 5;
			}
			else {
				CurrentStamina -= 1;
			}

		}
	}
}

void APsychicCH::HealthCalc()
{
	
	if(Endurance > 0)
	{
		int EnduranceMultiplier = 15;

		Health = Endurance * EnduranceMultiplier;
		CurrentHealth = Health;
		HealthRegen = Endurance / 200;

	}
	
}

void APsychicCH::StaminaCalc()
{
	if(Endurance > 0)
	{
		int EnduranceMultiplier = 100;

		Stamina = Endurance * EnduranceMultiplier;
		CurrentStamina = Stamina;
		StaminaRegen = Endurance / 10.f;
	}
}

void APsychicCH::EnergyCalc()
{
	int Mainstat = Mystic;
	if (Mainstat > 0)
	{
		Energy = Mainstat * 10.f;

		CurrentEnergy = Energy;

		EnergyRegen = (Mainstat / 200.f);

	}
}

void APsychicCH::RegenCalc()
{
	
	Timer -= 1;
	if (Timer == 0.f) 
	{
		if (CurrentEnergy < Energy) {
			CurrentEnergy += EnergyRegen;
		}
		if (CurrentStamina < Stamina) {
			CurrentStamina += StaminaRegen;
		}
		if (CurrentHealth < Health) {
			CurrentHealth += HealthRegen;
		}
		Timer = 30.f;
	}
}

void APsychicCH::PsychicSpear()
{

	if (CurrentEnergy >= 10) {
		//UE_LOG(LogTemp, Warning, TEXT("Shoot"));
		ActorLocation = GetActorLocation();
		NewSpawnLocation = FVector3d(ActorLocation.X , ActorLocation.Y , ActorLocation.Z + 50.f);
		GetWorld()->SpawnActor<AActor>(BP_Psychic_Lance,		// What to spawn
			NewSpawnLocation +50.f, GetActorRotation());	// Location & Rotation
		CurrentEnergy -= 10;
	}
	
}

void APsychicCH::Dash()
{
	
	Dashing = true;
}


void APsychicCH::HitBy_PB()
{
	CurrentHealth -= 10;
}

void APsychicCH::HitBy_PL()
{
	CurrentHealth -= 100;
}

void APsychicCH::PsychicBlast()
{
	if (CurrentEnergy >= 1) {
		//UE_LOG(LogTemp, Warning, TEXT("Shoot"));
		ActorLocation = GetActorLocation();
		NewSpawnLocation = FVector3d(ActorLocation.X , ActorLocation.Y, ActorLocation.Z + 100.f);
		GetWorld()->SpawnActor<AActor>(BP_Psychic_Blast,		// What to spawn
			NewSpawnLocation, GetActorRotation());	// Location & Rotation
		CurrentEnergy -= 1;
	}

}
