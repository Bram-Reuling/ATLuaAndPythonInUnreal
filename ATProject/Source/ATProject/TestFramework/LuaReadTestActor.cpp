// Fill out your copyright notice in the Description page of Project Settings.


#include "LuaReadTestActor.h"

ALuaReadTestActor::ALuaReadTestActor()
{
}

void ALuaReadTestActor::Test(int NumberOfActions)
{
	Super::Test(NumberOfActions);

	// Time Test
	for (int index = 0; index < NumberOfActions; index++)
	{
		TimerProfiler TimerProfiler;
		TimerProfiler.Start();
		
		const FString* Command = new FString("a = 1");
		const char* CharacterCommand = TCHAR_TO_ANSI(ToCStr(*Command));

		const int r = luaL_dostring(Lua_State, CharacterCommand);

		if (r != LUA_OK)
		{
			UE_LOG(LogTemp, Warning, TEXT("luaL_dostring != LUA_OK"));
			return;
		}

		lua_getglobal(Lua_State, "a");
		if (lua_isnumber(Lua_State, -1))
		{
			float a = (float)lua_tonumber(Lua_State, -1);
		}

		TimerProfiler.Stop();

		//UE_LOG(LogTemp, Warning, TEXT("Time: %f microseconds"), TimerProfiler.GetDuration());
		TimerResults.Add(TimerProfiler.GetDuration());
	}


	// Memory Test
	for (int index = 0; index < NumberOfActions; index++)
	{
		MemoryProfiler MemoryProfiler;
		MemoryProfiler.Start();
		
		const FString* Command = new FString("a = 1");
		const char* CharacterCommand = TCHAR_TO_ANSI(ToCStr(*Command));

		const int r = luaL_dostring(Lua_State, CharacterCommand);

		if (r != LUA_OK)
		{
			UE_LOG(LogTemp, Warning, TEXT("luaL_dostring != LUA_OK"));
			return;
		}

		lua_getglobal(Lua_State, "a");
		if (lua_isnumber(Lua_State, -1))
		{
			float a = (float)lua_tonumber(Lua_State, -1);
		}

		MemoryProfiler.Stop();

		//UE_LOG(LogTemp, Warning, TEXT("Memory: %lld bytes"), MemoryProfiler.GetMemoryUsage());

		MemoryResults.Add(MemoryProfiler.GetMemoryUsage());
	}
}

void ALuaReadTestActor::ReadVariableFromLua()
{
}
