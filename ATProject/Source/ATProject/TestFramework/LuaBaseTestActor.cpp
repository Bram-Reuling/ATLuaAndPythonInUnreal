// Fill out your copyright notice in the Description page of Project Settings.


#include "LuaBaseTestActor.h"

ALuaBaseTestActor::ALuaBaseTestActor()
{
}

void ALuaBaseTestActor::SetupTestEnvironment()
{
	Lua_State = luaL_newstate();

	if (Lua_State == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Lua_State == nullptr"));
		return;
	}

	luaL_openlibs(Lua_State);
	
	Super::SetupTestEnvironment();
}

void ALuaBaseTestActor::BreakdownTestEnvironment()
{
	lua_close(Lua_State);
	Lua_State = nullptr;
	
	Super::BreakdownTestEnvironment();
}
