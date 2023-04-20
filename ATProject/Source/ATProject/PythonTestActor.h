// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PythonLibrary/Python.h"
#include "PythonTestActor.generated.h"

UCLASS()
class ATPROJECT_API APythonTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APythonTestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void InitializePython();

	FString ScriptFolderPath;
	FString FullScriptPath;
	char* FullFilePath = nullptr;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FString PythonScriptFileName = "script";

	PyObject* pModuleName = nullptr;
	PyObject* pModule = nullptr;

	TMap<FString, PyObject*> PythonFunctionObjects;

	TArray<FString> PythonFunctions =
	{
		"PrintUnrealFromPython",
		"BeginPlay",
		"Tick"
	};
};
