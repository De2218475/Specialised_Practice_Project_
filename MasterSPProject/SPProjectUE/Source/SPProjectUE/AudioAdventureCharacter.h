#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

private:

	bool bIsRunning;
	float runSpeedMulti;

};
