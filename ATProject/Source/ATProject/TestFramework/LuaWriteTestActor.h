// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuaBaseTestActor.h"
#include "LuaWriteTestActor.generated.h"

/**
 * 
 */
UCLASS()
class ATPROJECT_API ALuaWriteTestActor : public ALuaBaseTestActor
{
	GENERATED_BODY()

public:
	ALuaWriteTestActor();

	virtual void Test(int NumberOfActions) override;

	void WriteVariableToLua();
};
