// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnableTestActor.h"
#include "PythonLibrary/Python.h"
#include "SpawnablePythonMove.generated.h"

/**
 * 
 */
UCLASS()
class ATPROJECT_API ASpawnablePythonMove : public ASpawnableTestActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupTestEnvironment() override;
	virtual void BreakdownTestEnvironment() override;

public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void DoTick(float DeltaTime) override;

	inline static ASpawnablePythonMove* Instance = nullptr;

private:
	FString ScriptFolderPath;
	FString FullScriptPath;
	char* FullFilePath = nullptr;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FString PythonScriptFileName = "movescript";

	PyObject* pModuleName = nullptr;
	PyObject* pModule = nullptr;
	PyObject* pTickFunction = nullptr;
};
