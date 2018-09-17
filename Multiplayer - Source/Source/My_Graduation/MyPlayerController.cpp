// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"

AMy_GraduationCharacter *component;
AMy_GraduationCharacter *currentPlayer;
AStaticMeshActor *mesh;
AStaticMeshActor *ball;

AMyPlayerController::AMyPlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	for (TObjectIterator<AMy_GraduationCharacter> Itr; Itr; ++Itr)
	{
		component = *Itr;
		//ClientMessage(Itr->GetName());
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Itr->GetName())
		UE_LOG(LogTemp, Warning, TEXT("Player id is: %i"), component->playerID);
		if (component->GetName() == "ThirdPersonCharacter2_2")	//find the second player
		{
			currentPlayer = component;
			//this->Possess(currentPlayer);
			xPosition = currentPlayer->GetActorLocation().X;
			yPosition = currentPlayer->GetActorLocation().Y;
			zPosition = currentPlayer->GetActorLocation().Z;

			xRotation = currentPlayer->GetActorRotation().Pitch;
			yRotation = currentPlayer->GetActorRotation().Yaw;
			zRotation = currentPlayer->GetActorRotation().Roll;

			UE_LOG(LogTemp, Warning, TEXT("Player XXXXXX position is: %f"), xPosition);
		}
		myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		playerPosition = myCharacter->GetActorLocation();
		UE_LOG(LogTemp, Warning, TEXT("Player position is:%s"), *playerPosition.ToString());
		
	}

	for (TObjectIterator<AStaticMeshActor> ObjItr; ObjItr; ++ObjItr)
	{
		mesh = *ObjItr;
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ObjItr->GetName());
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ObjItr->GetActorLocation().ToString());
		if (mesh->GetName() == "Football")	//find the football
		{
			UE_LOG(LogTemp, Warning, TEXT("Hello"));
			ball = mesh;
			xBallPosition = ball->GetActorLocation().X;
			yBallPosition = ball->GetActorLocation().Y;
			zBallPosition = ball->GetActorLocation().Z;
			xBallRotation = ball->GetActorRotation().Pitch;
			yBallRotation = ball->GetActorRotation().Yaw;
			zBallRotation = ball->GetActorRotation().Roll;
		}
	}
}

void AMyPlayerController::UpdatePosition(float *xPos, float *yPos, float *zPos, float *xRot, float *yRot, float *zRot)
{
	xPosition = *xPos;
	yPosition = *yPos;
	zPosition = *zPos;
	xRotation = *xRot;
	yRotation = *yRot;
	zRotation = *zRot;
}

void AMyPlayerController::UpdateBallPosition(float *xBallPos, float *yBallPos, float *zBallPos, float *xBallRot, float *yBallRot, float *zBallRot)
{
	xBallPosition = *xBallPos;
	yBallPosition = *yBallPos;
	zBallPosition = *zBallPos;
	xBallRotation = *xBallRot;
	yBallRotation = *yBallRot;
	zBallRotation = *zBallRot;
}

void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (component->GetName() == "ThirdPersonCharacter2_2")	//Update the pesotion of the other player
	{
		currentPosition.X = xPosition;
		currentPosition.Y = yPosition;
		currentPosition.Z = zPosition;

		currentRotation.Pitch = xRotation;
		currentRotation.Yaw = yRotation;
		currentRotation.Roll = zRotation;

		currentPlayer->SetActorLocation(currentPosition, false);
		currentPlayer->SetActorRotation(currentRotation);
		//FVector abc = currentPlayer->GetActorLocation();
		//UE_LOG(LogTemp, Warning, TEXT("Player XXXXXX position is: %s"), *component->GetName());
		//UE_LOG(LogTemp, Warning, TEXT("Player XXXXXX position is: %s"), *abc.ToString());
		//FRotator bcd = currentPlayer->GetActorRotation();
		//UE_LOG(LogTemp, Warning, TEXT("Player XXXXXX position is: %s"), *bcd.ToString());
	}

	myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	playerPosition = myCharacter->GetActorLocation();
	playerRotation = myCharacter->GetActorRotation();
	//UE_LOG(LogTemp, Warning, TEXT("Player position is: %s"), *playerPosition.ToString());
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("PlayerPosition: %s"), *playerPosition.ToString()));

	//Update the position of the ball
	//Sets the position of the ball to the middle of the ball in both clients
	//Gets buggy so it's commented

	/*for (TObjectIterator<AStaticMeshActor> ObjItr; ObjItr; ++ObjItr)
	{
		mesh = *ObjItr;
		if (mesh->GetName() == "Football")
		{
			currentBallPosition.X = xBallPosition;
			currentBallPosition.Y = yBallPosition;
			currentBallPosition.Z = zBallPosition;

			currentBallRotation.Pitch = xBallPosition;
			currentBallRotation.Yaw = yBallPosition;
			currentBallRotation.Roll = zBallPosition;

			if (FVector::Dist(currentBallPosition, ballPosition) > 10000000)
			{
				FVector middle;
				FRotator middler = FRotator (0,0,0);
				middle.X = (currentBallPosition.X + ballPosition.X) / 2;
				middle.Y = (currentBallPosition.Y + ballPosition.Y) / 2;
				middle.Z = (currentBallPosition.Z + ballPosition.Z) / 2;
				ball->SetActorLocation(middle, false);
				ball->SetActorRotation(middler);
			}

			UE_LOG(LogTemp, Warning, TEXT("Ball position is: %s"), *ball->GetActorLocation().ToString());

			ballPosition = mesh->GetActorLocation();
			//ballRotation = mesh->GetActorRotation();
		}
	}*/
}

AMyPlayerController::~AMyPlayerController()
{

}



