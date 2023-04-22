// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuaBaseTestActor.h"
#include "LuaReadTestActor.generated.h"

/**
 * 
 */
UCLASS()
class ATPROJECT_API ALuaReadTestActor : public ALuaBaseTestActor
{
	GENERATED_BODY()

	ALuaReadTestActor();

	virtual void Test(int NumberOfActions) override;

	void ReadVariableFromLua();
};
