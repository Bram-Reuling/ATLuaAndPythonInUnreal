// Copyright Epic Games, Inc. All Rights Reserved.

#include "ATProjectGameMode.h"
#include "ATProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AATProjectGameMode::AATProjectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
