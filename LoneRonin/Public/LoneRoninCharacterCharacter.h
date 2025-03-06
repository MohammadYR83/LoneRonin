#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LoneRoninCharacterCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class LONERONIN_API ALoneRoninCharacterCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	ALoneRoninCharacterCharacter();	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
private:
	UPROPERTY(VisibleAnywhere);
	USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere);
	UCameraComponent* ViewCamera;
};
