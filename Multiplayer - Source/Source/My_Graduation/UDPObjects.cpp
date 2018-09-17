// Fill out your copyright notice in the Description page of Project Settings.

#include "UDPObjects.h"



UDPObjects::UDPObjects()
{
}

void UDPObjects::SetConnection()
{
	Communication.Connection(address, port);
}

void UDPObjects::SendData(AMyPlayerController *playerController, FString opponentIp, int32 opponentPort)
{
	while (runSend == true)
	{
		//UE_LOG(LogTemp, Warning, TEXT("qwe"));

		//convert the player and ball position to FString and separate its values by ','
		myPositionX = FString::SanitizeFloat(playerController->playerPosition.X);
		myPositionY = FString::SanitizeFloat(playerController->playerPosition.Y);
		myPositionZ = FString::SanitizeFloat(playerController->playerPosition.Z);

		myRotationX = FString::SanitizeFloat(playerController->playerRotation.Pitch);
		myRotationY = FString::SanitizeFloat(playerController->playerRotation.Yaw);
		myRotationZ = FString::SanitizeFloat(playerController->playerRotation.Roll);

		myBallPositionX = FString::SanitizeFloat(playerController->ballPosition.X);
		myBallPositionY = FString::SanitizeFloat(playerController->ballPosition.Y);
		myBallPositionZ = FString::SanitizeFloat(playerController->ballPosition.Z);

		myBallRotationX = FString::SanitizeFloat(playerController->ballRotation.Pitch);
		myBallRotationY = FString::SanitizeFloat(playerController->ballRotation.Yaw);
		myBallRotationZ = FString::SanitizeFloat(playerController->ballRotation.Roll);

		messageSent.Append(myPositionX);
		messageSent.Append(",");
		messageSent.Append(myPositionY);
		messageSent.Append(",");
		messageSent.Append(myPositionZ);
		messageSent.Append(",");

		messageSent.Append(myRotationX);
		messageSent.Append(",");
		messageSent.Append(myRotationY);
		messageSent.Append(",");
		messageSent.Append(myRotationZ);
		messageSent.Append(",");

		messageSent.Append(myBallPositionX);
		messageSent.Append(",");
		messageSent.Append(myBallPositionY);
		messageSent.Append(",");
		messageSent.Append(myBallPositionZ);
		messageSent.Append(",");

		messageSent.Append(myBallRotationX);
		messageSent.Append(",");
		messageSent.Append(myBallRotationY);
		messageSent.Append(",");
		messageSent.Append(myBallRotationZ);
		messageSent.Append(",");

		

		UE_LOG(LogTemp, Warning, TEXT("Message '%s' to '%s:%i'"), *messageSent, *opponentIp, opponentPort);
		Communication.SendMessage(messageSent, opponentIp, opponentPort);
		messageSent.Empty();	//otherwise it will stack
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

void UDPObjects::ReceiveData(AMyPlayerController *playerController)
{
	while (runReceive == true)
	{
		//UE_LOG(LogTemp, Warning, TEXT("asd"));

		messageReceived = Communication.ReceiveMessage();

		if (messageReceived.IsEmpty() == false) //dont bother with empty messages
		{
			//detect each parameter separated by the ','
			//convert them back to floats
			messageReceived.ParseIntoArray(positionAndRotation, TEXT(","), true);
			xPosition = FCString::Atof(*positionAndRotation[0]);
			yPosition = FCString::Atof(*positionAndRotation[1]);
			zPosition = FCString::Atof(*positionAndRotation[2]);

			xRotation = FCString::Atof(*positionAndRotation[3]);
			yRotation = FCString::Atof(*positionAndRotation[4]);
			zRotation = FCString::Atof(*positionAndRotation[5]);

			xBallPosition = FCString::Atof(*positionAndRotation[6]);
			yBallPosition = FCString::Atof(*positionAndRotation[7]);
			zBallPosition = FCString::Atof(*positionAndRotation[8]);

			xBallRotation = FCString::Atof(*positionAndRotation[9]);
			yBallRotation = FCString::Atof(*positionAndRotation[10]);
			zBallRotation = FCString::Atof(*positionAndRotation[11]);
		}

		//send the data to the player controller to update the other player
		playerController->UpdatePosition(&xPosition, &yPosition, &zPosition, &xRotation, &yRotation, &zRotation);
		playerController->UpdateBallPosition(&xBallPosition, &yBallPosition, &zBallPosition, &xBallRotation, &yBallRotation, &zBallRotation);

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

UDPObjects::~UDPObjects()
{
}
