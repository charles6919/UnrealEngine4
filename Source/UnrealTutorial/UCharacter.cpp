// Fill out your copyright notice in the Description page of Project Settings.


#include "UCharacter.h"

// Sets default values
AUCharacter::AUCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//컴포넌트 초기화
	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINGARM"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	//컴포넌트 ㅅ
	mSpringArm->SetupAttachment(this->GetCapsuleComponent());
	mCamera->SetupAttachment(mSpringArm);

	this->GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));
	mSpringArm->TargetArmLength = 400.0f;
	mSpringArm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	//메쉬 생성
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> 
		SK_CARDBOARD(TEXT("/Game/InfinityBladeWarriors/Character/CompleteCharacters/SK_CharM_Cardboard.SK_CharM_Cardboard"));
	if (SK_CARDBOARD.Succeeded())
	{
		this->GetMesh()->SetSkeletalMesh(SK_CARDBOARD.Object);
	}

	//애니메이션 BP 생성
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance>
		WARRIOR_ANIM(TEXT("/Game/Book/Animations/WarriorAnimBP.WarriorAnimBP_C"));
	if (WARRIOR_ANIM.Succeeded())
	{
		this->GetMesh()->SetAnimInstanceClass(WARRIOR_ANIM.Class);
	}

	SetControlMode(EControlMode::GTA);

	mArmLengthSpeed = 3.0f;
	mArmRotationSpeed = 10.0f;
}

// Called when the game starts or when spawned
void AUCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AUCharacter::SetControlMode(EControlMode NewControlMode)
{
	mCurrentControlMode = NewControlMode;

	switch (mCurrentControlMode)
	{

	case EControlMode::GTA:
	{
		//mSpringArm->TargetArmLength = 450.0f;
		//mSpringArm->SetRelativeRotation(FRotator::ZeroRotator);
		mArmLengthTo = 450.0f;
		mSpringArm->bUsePawnControlRotation = true;
		mSpringArm->bInheritPitch = true;
		mSpringArm->bInheritRoll = true;
		mSpringArm->bInheritYaw = true;
		mSpringArm->bDoCollisionTest = true;
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;			//캐릭터가 움직이는 방향으로 부드럽게 움직여주는 기능
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);//회전하는 속도 설정
		break;
	}

	case EControlMode::DIBLO:
	{
		//mSpringArm->TargetArmLength = 800.0f;
		//mSpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
		mArmLengthTo = 800.0f;
		mArmRotationTo = FRotator(-45.0f, 0.0f, 0.0f);
		mSpringArm->bUsePawnControlRotation = false;
		mSpringArm->bInheritPitch = false;
		mSpringArm->bInheritRoll = false;
		mSpringArm->bInheritYaw = false;
		mSpringArm->bDoCollisionTest = false;
		bUseControllerRotationYaw = true;
		break;
	}

	}//switch(ControlMode) End
}

// Called every frame
void AUCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	mSpringArm->TargetArmLength = FMath::FInterpTo(mSpringArm->TargetArmLength, this->mArmLengthTo, DeltaTime, this->mArmLengthSpeed);


	switch (mCurrentControlMode)
	{

	case EControlMode::DIBLO:
	{
		mSpringArm->SetRelativeRotation(
			FMath::RInterpTo(mSpringArm->GetRelativeRotation(), this->mArmRotationTo, DeltaTime, this->mArmRotationSpeed));

		if (mDirectionToMove.SizeSquared() > 0.0f)
		{
			GetController()->SetControlRotation(FRotationMatrix::MakeFromX(mDirectionToMove).Rotator());
			AddMovementInput(mDirectionToMove);
		}
		break;
	}//Switch(mCurrentControlMode) End

	}

}

// Called to bind functionality to input
void AUCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("UpDown"), this, &AUCharacter::UpDown);
	PlayerInputComponent->BindAxis(TEXT("LeftRight"), this, &AUCharacter::LeftRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AUCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AUCharacter::Turn);

	PlayerInputComponent->BindAction(TEXT("ChangeControlMode"), EInputEvent::IE_Pressed, this, &AUCharacter::ChangeView);
}

void AUCharacter::UpDown(float NewAxisValue)
{
	switch (mCurrentControlMode)
	{
	case EControlMode::GTA:
		AddMovementInput(FRotationMatrix(this->GetControlRotation()).GetUnitAxis(EAxis::X), NewAxisValue, false);//컨트롤러가 회전한 방향의 앞쪽(X)축에 따라 이동
		break;

	case EControlMode::DIBLO:
		mDirectionToMove.X = NewAxisValue;
	}

	ULOG(Warning, TEXT("%f"), NewAxisValue);
	
}

void AUCharacter::LeftRight(float NewAxisValue)
{
	switch (mCurrentControlMode)
	{
	case EControlMode::GTA:
		AddMovementInput(FRotationMatrix(this->GetControlRotation()).GetUnitAxis(EAxis::Y), NewAxisValue, false);//컨트롤러가 회전한 방향의 오른쪽(Y)축에 따라 이동
		break;

	case EControlMode::DIBLO:
		mDirectionToMove.Y = NewAxisValue;
	}

	ULOG(Warning, TEXT("%f"), NewAxisValue);
	
}

void AUCharacter::LookUp(float NewAxisValue)
{
	switch (mCurrentControlMode)
	{
	case EControlMode::GTA:
		AddControllerPitchInput(NewAxisValue);
		break;
	}
	ULOG(Warning, TEXT("%f"), NewAxisValue);
}
	

void AUCharacter::Turn(float NewAxisValue)
{
	switch (mCurrentControlMode)
	{
	case EControlMode::GTA:
		AddControllerYawInput(NewAxisValue);
		break;
	}
	ULOG(Warning, TEXT("%f"), NewAxisValue);
}

void AUCharacter::ChangeView()
{

	switch (mCurrentControlMode)
	{
	case EControlMode::GTA:
		GetController()->SetControlRotation(GetActorRotation());
		SetControlMode(EControlMode::DIBLO);
		break;

	case EControlMode::DIBLO:
		GetController()->SetControlRotation(mSpringArm->GetRelativeRotation());
		SetControlMode(EControlMode::GTA);
		break;

	}
}

