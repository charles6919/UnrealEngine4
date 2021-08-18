// Fill out your copyright notice in the Description page of Project Settings.


#include "UPawn.h"

// Sets default values
AUPawn::AUPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CAPSULE"));
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	mMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MOVEMENT"));
	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	RootComponent = mCapsule;
	mMesh->SetupAttachment(mCapsule);
	mSpringArm->SetupAttachment(mCapsule);
	mCamera->SetupAttachment(mSpringArm);

	mCapsule->SetCapsuleHalfHeight(88.0f);
	mCapsule->SetCapsuleRadius(34.0f);
	mMesh->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	mSpringArm->TargetArmLength = 400.0f;
	mSpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> 
		SK_CARDBOARD(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if (SK_CARDBOARD.Succeeded())
	{
		mMesh->SetSkeletalMesh(SK_CARDBOARD.Object);
	}

	mMesh->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	static ConstructorHelpers::FClassFinder<UAnimInstance> WARRIOR_ANIM(TEXT("/Game/Book/Animations/WarriorAnimBP.WarriorAnimBP_C"));
	if (WARRIOR_ANIM.Succeeded())
	{
		mMesh->SetAnimInstanceClass(WARRIOR_ANIM.Class);
	}
}

void AUPawn::UpDown(float NewAxisValue)
{
	ULOG(Warning, TEXT("%f"), NewAxisValue);
	AddMovementInput(GetActorForwardVector(), NewAxisValue);
}

void AUPawn::LeftRight(float NewAxisValue)
{
	ULOG(Warning, TEXT("%f"), NewAxisValue);
	AddMovementInput(GetActorRightVector(), NewAxisValue);
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

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AUPawn::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AUPawn::LeftRight);
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

