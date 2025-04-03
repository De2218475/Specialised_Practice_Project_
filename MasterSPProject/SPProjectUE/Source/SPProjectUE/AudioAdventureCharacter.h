#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "AudioAdventureCharacter.generated.h"

UCLASS()
class SPPROJECTUE_API AAudioAdventureCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAudioAdventureCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	void MoveX(float axisVal);
	void MoveY(float axisVal);

	void StartRun();
	void StartWalk();

	// Crouching functions
	void StartCrouch();
	void StopCrouch();

	void Ray();

private:

	bool bIsRunning;
	float runSpeedMulti;

	bool bIsCrouching;
	float crouchSpeedMulti;
};