// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "My_GraduationGameMode.h"
#include "My_GraduationCharacter.h"
#include "MyPlayerController.h"
#include "UObject/ConstructorHelpers.h"

AMy_GraduationGameMode::AMy_GraduationGameMode()
{
	PlayerControllerClass = AMyPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
