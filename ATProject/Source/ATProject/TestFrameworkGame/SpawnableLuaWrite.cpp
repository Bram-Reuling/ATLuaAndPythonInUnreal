// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnableLuaWrite.h"

#include "ATProject/TestFramework/TimerProfiler.h"

void ASpawnableLuaWrite::BeginPlay()
{
	TestDescriptor = "LuaWrite";
	Super::BeginPlay();
}

void ASpawnableLuaWrite::SetupTestEnvironment()
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

void ASpawnableLuaWrite::BreakdownTestEnvironment()
{
	lua_close(Lua_State);
	Lua_State = nullptr;
	
	Super::BreakdownTestEnvironment();
}

void ASpawnableLuaWrite::DoTick(float DeltaTime)
{
	Super::DoTick(DeltaTime);
	
	const char* CharacterCommand = "a = 1";

	if (luaL_dostring(Lua_State, CharacterCommand) != LUA_OK)
	{
		UE_LOG(LogTemp, Warning, TEXT("luaL_dostring != LUA_OK"));
	}
}
