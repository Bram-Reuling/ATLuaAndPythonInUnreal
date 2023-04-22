// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTestActor.h"

// Sets default values
ABaseTestActor::ABaseTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ABaseTestActor::CalculateAverages()
{
	float TotalTime = 0;
	SIZE_T TotalMemory = 0;
	float TotalFPS = 0;

	for (const float Time : TimerResults)
	{
		TotalTime += Time;
	}

	for (const SIZE_T Memory : MemoryResults)
	{
		TotalMemory += Memory;
	}

	for (const float FPS : FPSResults)
	{
		//TotalFPS += FPS;
	}

	if (TotalTime == 0 || TotalMemory == 0) return;
	
	AverageTimerResult = TotalTime / TimerResults.Num();
	AverageMemoryResult = TotalMemory / MemoryResults.Num();
	//AverageFPSResult = TotalFPS / TotalNumberOfActions;
}

void ABaseTestActor::SetupTestEnvironment()
{
	TestStartDelegate.Broadcast();
}

void ABaseTestActor::BreakdownTestEnvironment()
{
	TestDoneDelegate.Broadcast();
}

void ABaseTestActor::SetTestType(ETestType Type)
{
	TestType = Type;
}

ETestType ABaseTestActor::GetTestType() const
{
	return TestType;
}

float ABaseTestActor::GetAverageTimerResult() const
{
	return AverageTimerResult;
}

SIZE_T ABaseTestActor::GetAverageMemoryResult() const
{
	return AverageMemoryResult;
}

float ABaseTestActor::GetAverageFPSResult() const
{
	return AverageFPSResult;
}

FString ABaseTestActor::GetTestDescriptor() const
{
	return TestDescriptor;
}

void ABaseTestActor::PerformTest(int NumberOfActions)
{
	TotalNumberOfActions = NumberOfActions;

	SetupTestEnvironment();

	Test(TotalNumberOfActions);
	
	BreakdownTestEnvironment();
}

void ABaseTestActor::Test(int NumberOfActions) {}

