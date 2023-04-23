// Fill out your copyright notice in the Description page of Project Settings.


#include "PythonBaseTestActor.h"

APythonBaseTestActor::APythonBaseTestActor()
{
}

void APythonBaseTestActor::SetupTestEnvironment()
{
	Py_Initialize();
	Super::SetupTestEnvironment();
}

void APythonBaseTestActor::BreakdownTestEnvironment()
{
	Py_Finalize();
	Super::BreakdownTestEnvironment();
}
