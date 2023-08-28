// Fill out your copyright notice in the Description page of Project Settings.


#include "TPM_Fighter_GM.h"
#include "Kismet/GameplayStatics.h"



ATPM_Fighter_GM::ATPM_Fighter_GM()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATPM_Fighter_GM::BeginPlay()
{
	Super::BeginPlay();
	/*for(int i = 0;i<3;i++)
	UGameplayStatics::CreatePlayer(GetWorld(), i, true);*/

}


void ATPM_Fighter_GM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


