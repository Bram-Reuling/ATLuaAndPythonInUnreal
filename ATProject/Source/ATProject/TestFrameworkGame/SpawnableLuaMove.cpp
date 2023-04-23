// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnableLuaMove.h"

static int MoveActor(lua_State* L)
{
	if (ASpawnableLuaMove* Actor = ASpawnableLuaMove::Instance)
	{
		UE_LOG(LogTemp, Warning, TEXT("MoveActor: Actor Found!"));
		const FVector CurrentPosition = Actor->GetActorLocation();
		const FVector NewPosition = CurrentPosition + FVector::One();

		Actor->SetActorLocation(NewPosition);	
	}
	
	return 0;
}

void ASpawnableLuaMove::BeginPlay()
{
	TestDescriptor = "LuaMove";
	Instance = this;
	Super::BeginPlay();
}

void ASpawnableLuaMove::SetupTestEnvironment()
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

	lua_register(Lua_State, "MoveActor", MoveActor);
	
	luaL_dofile(Lua_State, FullFilePath);
	
	Super::SetupTestEnvironment();
}

void ASpawnableLuaMove::BreakdownTestEnvironment()
{
	lua_close(Lua_State);
	Lua_State = nullptr;
	Instance = nullptr;
	
	Super::BreakdownTestEnvironment();
}

void ASpawnableLuaMove::Tick(float DeltaSeconds)
{
	lua_getglobal(Lua_State, "Tick");
	if (lua_isfunction(Lua_State, -1))
	{
		Super::Tick(DeltaSeconds);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Tick is not a function"));
	}
}

void ASpawnableLuaMove::DoTick(float DeltaTime)
{
	if (lua_pcall(Lua_State, 0, 0, 0) != LUA_OK)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant Tick"));
	}
}
