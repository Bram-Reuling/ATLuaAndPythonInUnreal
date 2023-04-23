// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnableTestActor.h"

extern "C"
{
#include "LuaLibrary/lua.h"
#include "LuaLibrary/lauxlib.h"
#include "LuaLibrary/lualib.h"
}

#include "SpawnableLuaWrite.generated.h"

/**
 * 
 */
UCLASS()
class ATPROJECT_API ASpawnableLuaWrite : public ASpawnableTestActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupTestEnvironment() override;
	virtual void BreakdownTestEnvironment() override;

	lua_State* Lua_State = nullptr;

public:
	virtual void DoTick(float DeltaTime) override;
};
