// Fill out your copyright notice in the Description page of Project Settings.


#include "UPawn.h"

// Sets default values
AUPawn::AUPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AUPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	ULOG_S(Warning);
}

void AUPawn::PossessedBy(AController* NewController)
{
	ULOG_S(Warning);
	Super::PossessedBy(NewController);
}

