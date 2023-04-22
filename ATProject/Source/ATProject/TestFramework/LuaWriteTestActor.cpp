// Fill out your copyright notice in the Description page of Project Settings.


#include "LuaWriteTestActor.h"

ALuaWriteTestActor::ALuaWriteTestActor()
{
}

void ALuaWriteTestActor::Test(int NumberOfActions)
{
	Super::Test(NumberOfActions);

	// Time Test
	{
		for (int index = 0; index < NumberOfActions; index++)
		{
			TimerProfiler TimerProfiler;
			TimerProfiler.Start();
			WriteVariableToLua();

			TimerProfiler.Stop();

			//UE_LOG(LogTemp, Warning, TEXT("Time: %f microseconds"), TimerProfiler.GetDuration());
			TimerResults.Add(TimerProfiler.GetDuration());
		}
	}

	// Memory Test
	{
		for (int index = 0; index < NumberOfActions; index++)
		{
			MemoryProfiler MemoryProfiler;
			MemoryProfiler.Start();
			WriteVariableToLua();

			MemoryProfiler.Stop();

			//UE_LOG(LogTemp, Warning, TEXT("Memory: %lld bytes"), MemoryProfiler.GetMemoryUsage());

			MemoryResults.Add(MemoryProfiler.GetMemoryUsage());
		}
	}
	
	// FPS Test
	{
		for (int index = 0; index < NumberOfActions; index++)
		{
			WriteVariableToLua();
		}
	}
}

void ALuaWriteTestActor::WriteVariableToLua()
{
	const FString* Command = new FString("a = 1");
	const char* CharacterCommand = TCHAR_TO_ANSI(ToCStr(*Command));

	if (luaL_dostring(Lua_State, CharacterCommand) != LUA_OK)
	{
		UE_LOG(LogTemp, Warning, TEXT("luaL_dostring != LUA_OK"));
	}
}
