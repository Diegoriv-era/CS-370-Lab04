// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "TopDownShmupGameMode.h"
#include "TopDownShmup.h"
#include "TopDownShmupPlayerController.h"
#include "TopDownShmupCharacter.h"

ATopDownShmupGameMode::ATopDownShmupGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATopDownShmupPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
