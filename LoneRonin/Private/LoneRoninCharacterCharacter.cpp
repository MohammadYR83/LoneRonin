#include "LoneRoninCharacterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


ALoneRoninCharacterCharacter::ALoneRoninCharacterCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 300.f;
	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ViewComponent"));
	ViewCamera->SetupAttachment(SpringArm);
}
void ALoneRoninCharacterCharacter::BeginPlay()
{
	Super::BeginPlay();	
}
void ALoneRoninCharacterCharacter::MoveForward(float Value)
{
	if (Controller && (Value != 0.f))
	{
		const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
		AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X), Value);
	}
}
void ALoneRoninCharacterCharacter::MoveRight(float Value)
{
	if (Controller && (Value != 0.f))
	{
		const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
		AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y), Value);
	}
}
void ALoneRoninCharacterCharacter::Turn(float Value)
{
	AddControllerYawInput(Value);
}
void ALoneRoninCharacterCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}
void ALoneRoninCharacterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void ALoneRoninCharacterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &ALoneRoninCharacterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &ALoneRoninCharacterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(FName("Turn"), this, &ALoneRoninCharacterCharacter::Turn);
	PlayerInputComponent->BindAxis(FName("LookUp"), this, &ALoneRoninCharacterCharacter::LookUp);
}

