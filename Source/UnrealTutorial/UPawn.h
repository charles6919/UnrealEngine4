// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealTutorial.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "UPawn.generated.h"

UCLASS()
class UNREALTUTORIAL_API AUPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AUPawn();

private:
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void PostInitializeComponents() override;
	virtual void PossessedBy(AController* NewController) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, Category=Collision)
	UCapsuleComponent* mCapsule;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* mMesh;

	UPROPERTY(VisibleAnywhere, Category=Visual)
	UFloatingPawnMovement* mMovement;

	UPROPERTY(VisibleAnywhere, Category=Camera)
	USpringArmComponent* mSpringArm;

	UPROPERTY(VisibleAnywhere, Category=Camera)
	UCameraComponent* mCamera;



};
