#include "AudioAdventureCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AAudioAdventureCharacter::AAudioAdventureCharacter()
{
	// Set this character to call Tick() every frame.  
	PrimaryActorTick.bCanEverTick = true;

	bIsRunning = false;
	runSpeedMulti = 1.8f;

	bIsCrouching = false;
	crouchSpeedMulti = 0.75f; // Crouching reduces speed to 50%

	// Set default movement settings
	UCharacterMovementComponent* CharMovement = GetCharacterMovement();
	if (CharMovement)
	{
		CharMovement->GravityScale = 2.0f;
		CharMovement->MaxWalkSpeed = 250.0f;
		CharMovement->AirControl = 1.0f;
		CharMovement->JumpZVelocity = 600.0f;
		CharMovement->NavAgentProps.bCanCrouch = true; // Enable crouching
		CharMovement->bCanWalkOffLedgesWhenCrouching = true;
		CharMovement->MaxWalkSpeedCrouched = 150.f;
		CharMovement->GroundFriction = 4.0f;
		CharMovement->BrakingDecelerationWalking = 0.0f;
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

	// Bind Crouch actions
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &AAudioAdventureCharacter::StartCrouch);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &AAudioAdventureCharacter::StopCrouch);
}

void AAudioAdventureCharacter::MoveX(float axisVal)
{
	float currentSpeed = bIsRunning ? runSpeedMulti : 1.0f;
	currentSpeed = bIsCrouching ? crouchSpeedMulti : currentSpeed;
	AddMovementInput(GetActorForwardVector() * axisVal * currentSpeed);
}

void AAudioAdventureCharacter::MoveY(float axisVal)
{
	float currentSpeed = bIsRunning ? runSpeedMulti : 1.0f;
	currentSpeed = bIsCrouching ? crouchSpeedMulti : currentSpeed;
	AddMovementInput(GetActorRightVector() * axisVal * currentSpeed);
}

void AAudioAdventureCharacter::StartRun()
{
	if (!bIsCrouching) // Prevent running while crouching
	{
		bIsRunning = true;
		UCharacterMovementComponent* CharMovement = GetCharacterMovement();
		if (CharMovement)
		{
			CharMovement->MaxWalkSpeed *= runSpeedMulti; // Increase movement speed
		}
	}
}

void AAudioAdventureCharacter::StartWalk()
{
	bIsRunning = false;
	UCharacterMovementComponent* CharMovement = GetCharacterMovement();
	if (CharMovement)
	{
		CharMovement->MaxWalkSpeed /= runSpeedMulti; // Reset to walking speed
	}
}

void AAudioAdventureCharacter::StartCrouch()
{
	if (!bIsCrouching)
	{
		bIsCrouching = true;
		Crouch();
		UCharacterMovementComponent* CharMovement = GetCharacterMovement();
		if (CharMovement)
		{
			CharMovement->MaxWalkSpeed *= crouchSpeedMulti; // Reduce speed when crouching
		}
	}
}

void AAudioAdventureCharacter::StopCrouch()
{
	if (bIsCrouching)
	{
		bIsCrouching = false;
		UnCrouch();
		UCharacterMovementComponent* CharMovement = GetCharacterMovement();
		if (CharMovement)
		{
			CharMovement->MaxWalkSpeed /= crouchSpeedMulti; // Reset to normal speed
		}
	}
}