// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTestActor.h"
#include "PythonLibrary/Python.h"
#include "PythonBaseTestActor.generated.h"

/**
 * 
 */
UCLASS()
class ATPROJECT_API APythonBaseTestActor : public ABaseTestActor
{
	GENERATED_BODY()

public:
	APythonBaseTestActor();

protected:
	virtual void SetupTestEnvironment() override;
	virtual void BreakdownTestEnvironment() override;
};
