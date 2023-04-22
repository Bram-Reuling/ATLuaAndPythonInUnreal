// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTestActor.h"

// Sets default values
ABaseTestActor::ABaseTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
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

TArray<long long> ABaseTestActor::GetTimerResults() const
{
	return TimerResults;
}

TArray<SIZE_T> ABaseTestActor::GetMemoryResults() const
{
	return MemoryResults;
}

TArray<float> ABaseTestActor::GetFPSResults() const
{
	return FPSResults;
}

void ABaseTestActor::PerformTest(int NumberOfAction) {}

