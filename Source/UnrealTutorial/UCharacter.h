// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UnrealTutorial.h"
#include "GameFramework/Character.h"
#include "UCharacter.generated.h"

UCLASS()
class UNREALTUTORIAL_API AUCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUCharacter();

protected:
	enum class EControlMode
	{
		GTA = 0,
		DIBLO
	};

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetControlMode(EControlMode NewControlMode);

	//UPROPERTY�� �������� �ʴ� �������� �׻� �̷��� �ʱⰪ�� �����صδ� ���� �����ϴ�.
	EControlMode mCurrentControlMode = EControlMode::GTA;
	FVector mDirectionToMove = FVector::ZeroVector;

	//�ε巯�� ī�޶� ��ȯ�� ���� ����
	float mArmLengthTo = 0.0f;
	FRotator mArmRotationTo = FRotator::ZeroRotator;
	float mArmLengthSpeed = 0.0f;
	float mArmRotationSpeed = 0.0f;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	USpringArmComponent* mSpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera)
	UCameraComponent* mCamera;

private:
	//���� ���� �Լ�
	void UpDown(float NewAxisValue);
	void LeftRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);
	void ChangeView();
};
