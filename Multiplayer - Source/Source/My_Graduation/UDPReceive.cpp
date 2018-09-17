// Fill out your copyright notice in the Description page of Project Settings.

#include "UDPReceive.h"

UDPReceive::UDPReceive()
{
}


void UDPReceive::ReceiveData(AMyPlayerController *playerController)
{
	while (runReceive == true)
	{ 
		//UE_LOG(LogTemp, Warning, TEXT("asd"));
		
		messageReceived = Communication.ReceiveMessage();

		messageReceived.ParseIntoArray(positionAndRotation, TEXT(","), true);

		xPosition = FCString::Atof(*positionAndRotation[0]);
		yPosition = FCString::Atof(*positionAndRotation[1]);
		zPosition = FCString::Atof(*positionAndRotation[2]);

		xRotation = FCString::Atof(*positionAndRotation[3]);
		yRotation = FCString::Atof(*positionAndRotation[4]);
		zRotation = FCString::Atof(*positionAndRotation[5]);

		playerController->UpdatePosition(&xPosition, &yPosition, &zPosition, &xRotation, &yRotation, &zRotation);
		
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
}

UDPReceive::~UDPReceive()
{
}
