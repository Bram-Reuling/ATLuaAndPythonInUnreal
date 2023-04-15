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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
