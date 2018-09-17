// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "My_GraduationCharacter.h"
#include "EngineUtils.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/UObjectIterator.h"
#include <EngineGlobals.h>
#include <Runtime/Engine/Classes/Engine/Engine.h>
#include "Runtime/CoreUObject/Public/CoreUObject.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MY_GRADUATION_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()


public:

	AMyPlayerController();
	~AMyPlayerController();

	ACharacter *myCharacter;
	AStaticMeshActor *myBall;

	float xPosition;
	float yPosition;
	float zPosition;
	float xRotation;
	float yRotation;
	float zRotation;

	float xBallPosition;
	float yBallPosition;
	float zBallPosition;
	float xBallRotation;
	float yBallRotation;
	float zBallRotation;

	FVector playerPosition;
	FRotator playerRotation;
	FVector currentPosition;
	FRotator currentRotation;

	FVector ballPosition;
	FRotator ballRotation;
	FVector currentBallPosition;
	FRotator currentBallRotation;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	void UpdatePosition(float *xPos, float *yPos, float *zPos, float *xRot, float *yRot, float *zRot);
	void UpdateBallPosition(float *xBallPos, float *yBallPos, float *zBallPos, float *xBallRot, float *yBallRot, float *zBallRot);
};
