// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ATankPawn::ATankPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank body"));
	RootComponent = BodyMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank turret"));
	TurretMesh->SetupAttachment(BodyMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);


}

// Called when the game starts or when spawned
void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATankPawn::MoveForward(float AxisValue)
{
	TargetForwardAxisValue = AxisValue;
}

void ATankPawn::RotateRight(float AxisValue)
{
	TargetRightAxisValue = AxisValue;
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector currentLocation = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector MovePosition = currentLocation + ForwardVector * MoveSpeed * TargetForwardAxisValue * DeltaTime;
	SetActorLocation(MovePosition, true);
	float yawRotation = RotationSpeed * TargetRightAxisValue * DeltaTime;
	FRotator currentRotation = GetActorRotation();
	yawRotation = currentRotation.Yaw + yawRotation;
	FRotator newRotation = FRotator(0, yawRotation, 0);
	SetActorRotation(newRotation);
	CurrentRightAxisValue = FMath::Lerp(CurrentRightAxisValue, TargetRightAxisValue, InterpolationKey);

	UE_LOG(LogTemp, Warning, TEXT("CurrentRightAxisValue = %f TargetRightAxisValue = %f"), CurrentRightAxisValue, TargetRightAxisValue);
	

	yawRotation = currentRotation.Yaw + yawRotation;

	
	SetActorRotation(newRotation);
	
}








// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



