// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnableTestActor.h"
#include "PythonLibrary/Python.h"
#include "SpawnablePythonWrite.generated.h"

/**
 * 
 */
UCLASS()
class ATPROJECT_API ASpawnablePythonWrite : public ASpawnableTestActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void SetupTestEnvironment() override;
	virtual void BreakdownTestEnvironment() override;

	PyObject* MainModule = nullptr;
	PyObject* GlobalDictionary = nullptr;
	PyObject* LocalDictionary = nullptr;

public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void DoTick(float DeltaTime) override;
};
