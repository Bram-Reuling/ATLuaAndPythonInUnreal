// Fill out your copyright notice in the Description page of Project Settings.


#include "LuaTestActor.h"

// Lua functions
static int PrintUnreal(lua_State* L)
{
	const char* textFromLua = lua_tostring(L, 1);
	
	UE_LOG(LogTemp, Log, TEXT("Called from Lua! Text send: %hs"), textFromLua);

	return 0;
}

// Sets default values
ALuaTestActor::ALuaTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALuaTestActor::BeginPlay()
{
	Super::BeginPlay();

	const FString cmd = "a = 7 + 11";

	FString RelativePath = FPaths::ProjectDir();

	RelativePath.Append("Scripts/Lua/script.lua");
	
	const char* file = TCHAR_TO_ANSI(*RelativePath);

	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	lua_register(L, "PrintUnreal", PrintUnreal);
	luaL_dofile(L, file);

	lua_getglobal(L, "PrintInUnrealThroughLua");
	lua_pcall(L, 0, 0, 0);
}

// Called every frame
void ALuaTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

