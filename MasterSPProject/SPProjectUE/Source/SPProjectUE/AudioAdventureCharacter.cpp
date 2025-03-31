#include "AudioAdventureCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAudioAdventureCharacter::AAudioAdventureCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsRunning = false;
	runSpeedMulti = 1.8f;

	// Set default walking speed (MaxWalkSpeed) in the CharacterMovementComponent
	UCharacterMovementComponent* CharMovement = GetCharacterMovement();
	if (CharMovement)
	{
		CharMovement->MaxWalkSpeed = 600.0f; // Default walking speed, you can adjust this
	}
}

// Called when the game starts or when spawned
void AAudioAdventureCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAudioAdventureCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAudioAdventureCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveX"), this, &AAudioAdventureCharacter::MoveX);
	PlayerInputComponent->BindAxis(TEXT("MoveY"), this, &AAudioAdventureCharacter::MoveY);
	PlayerInputComponent->BindAxis(TEXT("RotateX"), this, &AAudioAdventureCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("RotateY"), this, &AAudioAdventureCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AAudioAdventureCharacter::Jump);

	PlayerInputComponent->BindAction(TEXT("Run"), IE_Pressed, this, &AAudioAdventureCharacter::StartRun);
	PlayerInputComponent->BindAction(TEXT("Run"), IE_Released, this, &AAudioAdventureCharacter::StartWalk);
}

void AAudioAdventureCharacter::MoveX(float axisVal)
{
	float currentSpeed = bIsRunning ? runSpeedMulti : 1.0f;
	AddMovementInput(GetActorForwardVector() * axisVal * currentSpeed);
}

void AAudioAdventureCharacter::MoveY(float axisVal)
{
	float currentSpeed = bIsRunning ? runSpeedMulti : 1.0f;
	AddMovementInput(GetActorRightVector() * axisVal * currentSpeed);
}

void AAudioAdventureCharacter::StartRun()
{
	bIsRunning = true;

	// Increase MaxWalkSpeed when running
	UCharacterMovementComponent* CharMovement = GetCharacterMovement();
	if (CharMovement)
	{
		CharMovement->MaxWalkSpeed *= runSpeedMulti; // Increase movement speed
	}
}

void AAudioAdventureCharacter::StartWalk()
{
	bIsRunning = false;

	// Reset MaxWalkSpeed to normal walking speed
	UCharacterMovementComponent* CharMovement = GetCharacterMovement();
	if (CharMovement)
	{
		CharMovement->MaxWalkSpeed /= runSpeedMulti; // Reset to walking speed
	}
}
