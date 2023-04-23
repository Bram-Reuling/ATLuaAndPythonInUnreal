// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnableLuaRead.h"

void ASpawnableLuaRead::BeginPlay()
{
	TestDescriptor = "LuaRead";
	Super::BeginPlay();
}

void ASpawnableLuaRead::SetupTestEnvironment()
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

void ASpawnableLuaRead::BreakdownTestEnvironment()
{
	lua_close(Lua_State);
	Lua_State = nullptr;
	
	Super::BreakdownTestEnvironment();
}

void ASpawnableLuaRead::Tick(float DeltaSeconds)
{
	const char* CharacterCommand = "a = 1";

	const int r = luaL_dostring(Lua_State, CharacterCommand);

	if (r != LUA_OK)
	{
		UE_LOG(LogTemp, Warning, TEXT("luaL_dostring != LUA_OK"));
		return;
	}
	Super::Tick(DeltaSeconds);
}

void ASpawnableLuaRead::DoTick(float DeltaTime)
{
	lua_getglobal(Lua_State, "a");
	if (lua_isnumber(Lua_State, -1))
	{
		float a = (float)lua_tonumber(Lua_State, -1);
	}
}
