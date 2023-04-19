// Fill out your copyright notice in the Description page of Project Settings.


#include "LuaTestActor.h"

// Lua functions
static int PrintUnreal(lua_State* L)
{
	const char* textFromLua = lua_tostring(L, 1);
	
	UE_LOG(LogTemp, Log, TEXT("[C++ && UNREAL] %hs"), textFromLua);

	return 0;
}

// Sets default values
ALuaTestActor::ALuaTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

ALuaTestActor::~ALuaTestActor()
{
	Lua_State = nullptr;
}

// Called when the game starts or when spawned
void ALuaTestActor::BeginPlay()
{
	Super::BeginPlay();

	// File setup.
	ScriptFolderPath = FPaths::ProjectDir().Append("Scripts/Lua");
	FullScriptPath = ScriptFolderPath.Append("/").Append(LuaScriptFileName);
	FullFilePath = TCHAR_TO_ANSI(*FullScriptPath);

	// Start Lua.
	Lua_State = luaL_newstate();

	if (Lua_State == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Lua_State == nullptr"));
		return;
	}
	
	luaL_openlibs(Lua_State);

	// Register functions to Lua.
	lua_register(Lua_State, "PrintUnreal", PrintUnreal);
	luaL_dofile(Lua_State, FullFilePath);

	lua_getglobal(Lua_State, "BeginPlay");
	lua_pcall(Lua_State, 0, 0 ,0);
}

// Called every frame
void ALuaTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	lua_getglobal(Lua_State, "Tick");
	lua_pushnumber(Lua_State, DeltaTime);
	lua_pcall(Lua_State, 1, 0, 0);
}

