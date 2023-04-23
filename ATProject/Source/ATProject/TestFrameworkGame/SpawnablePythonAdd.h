// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnableTestActor.h"
#include "PythonLibrary/Python.h"
#include "SpawnablePythonAdd.generated.h"

/**
 * 
 */
UCLASS()
class ATPROJECT_API ASpawnablePythonAdd : public ASpawnableTestActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupTestEnvironment() override;
	virtual void BreakdownTestEnvironment() override;

public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void DoTick(float DeltaTime) override;

private:
	FString ScriptFolderPath;
	FString FullScriptPath;
	char* FullFilePath = nullptr;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FString PythonScriptFileName = "addscript";

	PyObject* pModuleName = nullptr;
	PyObject* pModule = nullptr;
	PyObject* pAddFunction = nullptr;
};
