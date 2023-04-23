// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PythonBaseTestActor.h"
#include "PythonWriteTestActor.generated.h"

/**
 * 
 */
UCLASS()
class ATPROJECT_API APythonWriteTestActor : public APythonBaseTestActor
{
	GENERATED_BODY()

public:
	APythonWriteTestActor();

	virtual void Test(int NumberOfActions) override;

	void WriteVariableToPython();
};
