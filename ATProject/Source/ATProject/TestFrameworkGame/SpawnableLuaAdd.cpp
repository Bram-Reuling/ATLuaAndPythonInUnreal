// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnableLuaAdd.h"

void ASpawnableLuaAdd::BeginPlay()
{
	TestDescriptor = "LuaAdd";
	Super::BeginPlay();
}

void ASpawnableLuaAdd::SetupTestEnvironment()
{
	// File setup.
	ScriptFolderPath = FPaths::ProjectDir().Append("Scripts/Lua");
	FullScriptPath = ScriptFolderPath;
	FullScriptPath.Append("/").Append(LuaScriptFileName).Append(".lua");
	FullFilePath = TCHAR_TO_ANSI(*FullScriptPath);
	
	Lua_State = luaL_newstate();

	if (Lua_State == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Lua_State == nullptr"));
		return;
	}

	luaL_openlibs(Lua_State);

	luaL_dofile(Lua_State, FullFilePath);
	
	Super::SetupTestEnvironment();
}

void ASpawnableLuaAdd::BreakdownTestEnvironment()
{
	lua_close(Lua_State);
	Lua_State = nullptr;
	
	Super::BreakdownTestEnvironment();
}

void ASpawnableLuaAdd::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASpawnableLuaAdd::DoTick(float DeltaTime)
{
	Super::DoTick(DeltaTime);
	lua_getglobal(Lua_State, "add");
	if (lua_isfunction(Lua_State, -1))
	{
		lua_pushnumber(Lua_State, DeltaTime);
		lua_pushnumber(Lua_State, 20);
		if (lua_pcall(Lua_State, 2, 0, 0) != LUA_OK)
		{
			UE_LOG(LogTemp, Error, TEXT("Cant add"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("add is not a function"));
	}
}
