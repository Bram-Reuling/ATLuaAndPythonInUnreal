// Fill out your copyright notice in the Description page of Project Settings.


#include "LuaTestActor.h"

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

	lua_State *L = luaL_newstate();

	const char* scriptString = TCHAR_TO_ANSI(*cmd);
	const int r = luaL_dostring(L, scriptString);

	if (r == LUA_OK)
	{
		lua_getglobal(L, "a");
		if (lua_isnumber(L, -1))
		{
			const float a_in_cpp = (float)lua_tonumber(L, -1);
			UE_LOG(LogTemp, Log, TEXT("a_in_cpp = %f"), a_in_cpp);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("ERROR"));
	}
}

// Called every frame
void ALuaTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

