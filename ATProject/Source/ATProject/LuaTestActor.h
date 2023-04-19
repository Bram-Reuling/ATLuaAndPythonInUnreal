// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

extern "C"
{
#include "LuaLibrary/lua.h"
#include "LuaLibrary/lauxlib.h"
#include "LuaLibrary/lualib.h"
}

#include "LuaTestActor.generated.h"

UCLASS()
class ATPROJECT_API ALuaTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALuaTestActor();
	~ALuaTestActor();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	lua_State* Lua_State = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	FString ScriptFolderPath;
	FString FullScriptPath;
	char* FullFilePath = nullptr;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FString LuaScriptFileName = "script.lua";
};
