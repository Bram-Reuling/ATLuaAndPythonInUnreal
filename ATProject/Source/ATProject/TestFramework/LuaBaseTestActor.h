// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTestActor.h"

extern "C"
{
#include "LuaLibrary/lua.h"
#include "LuaLibrary/lauxlib.h"
#include "LuaLibrary/lualib.h"
}

#include "LuaBaseTestActor.generated.h"

/**
 * 
 */
UCLASS()
class ATPROJECT_API ALuaBaseTestActor : public ABaseTestActor
{
	GENERATED_BODY()

public:
	ALuaBaseTestActor();

protected:

	lua_State* Lua_State = nullptr;
	
	virtual void SetupTestEnvironment() override;
	virtual void BreakdownTestEnvironment() override;
};
