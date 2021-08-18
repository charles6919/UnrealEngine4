// Fill out your copyright notice in the Description page of Project Settings.


#include "UCharacter.h"

// Sets default values
AUCharacter::AUCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//������Ʈ �ʱ�ȭ
	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	//������Ʈ ��
	mSpringArm->SetupAttachment(this->GetCapsuleComponent());
	mCamera->SetupAttachment(mSpringArm);

	this->GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	mSpringArm->TargetArmLength = 400.0f;
	mSpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	//�޽� ����
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> 
		SK_CARDBOARD(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if (SK_CARDBOARD.Succeeded())
	{
		this->GetMesh()->SetSkeletalMesh(SK_CARDBOARD.Object);
	}

	//�ִϸ��̼� BP ����
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		WARRIOR_ANIM(TEXT("/Game/Book/Animations/WarriorAnimBP.WarriorAnimBP_C"));
	if (WARRIOR_ANIM.Succeeded())
	{
		this->GetMesh()->SetAnimInstanceClass(WARRIOR_ANIM.Class);
	}
}

// Called when the game starts or when spawned
void AUCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AUCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AUCharacter::LeftRight);
}

void AUCharacter::UpDown(float NewAxisValue)
{
	ULOG(Warning, TEXT("%f"), NewAxisValue);
	AddMovementInput(this->GetActorForwardVector(), NewAxisValue, false);
}

void AUCharacter::LeftRight(float NewAxisValue)
{
	ULOG(Warning, TEXT("%f"), NewAxisValue);
	AddMovementInput(this->GetActorRightVector(), NewAxisValue, false);
}

