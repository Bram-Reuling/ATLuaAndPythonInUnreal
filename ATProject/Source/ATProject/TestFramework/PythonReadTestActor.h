// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PythonBaseTestActor.h"
#include "PythonReadTestActor.generated.h"

/**
 * 
 */
UCLASS()
class ATPROJECT_API APythonReadTestActor : public APythonBaseTestActor
{
	GENERATED_BODY()

public:
	APythonReadTestActor();

	virtual void Test(int NumberOfActions) override;
};
