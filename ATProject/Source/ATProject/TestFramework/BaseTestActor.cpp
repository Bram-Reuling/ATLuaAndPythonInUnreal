// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTestActor.h"

#include "MemoryProfiler.h"
#include "TimerProfiler.h"

// Sets default values
ABaseTestActor::ABaseTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ABaseTestActor::BeginPlay()
{
	PerformTest();
	Super::BeginPlay();
}

void ABaseTestActor::SetupTestEnvironment() {}

void ABaseTestActor::BreakdownTestEnvironment() {}

void ABaseTestActor::PerformTest()
{
	int value = 0;

	UE_LOG(LogTemp, Warning, TEXT("Starting timer test."));
	
	TimerProfiler Timer;
	Timer.Start();
	for (int i = 0; i < 1000000; i++)
		value += 2;
	UE_LOG(LogTemp, Warning, TEXT("Result: %d"), value);
	Timer.Stop();
	
	UE_LOG(LogTemp, Warning, TEXT("Code execution: %lld μs"), Timer.GetDuration());

	value = 0;

	UE_LOG(LogTemp, Warning, TEXT("Starting mem test."));

	MemoryProfiler MemoryProfiler;
	MemoryProfiler.Start();
	for (int i = 0; i < 1000000; i++)
		value += 2;

	TimerProfiler *NewTimer = new TimerProfiler();
	
	UE_LOG(LogTemp, Warning, TEXT("Result: %d"), value);
	MemoryProfiler.End();

	UE_LOG(LogTemp, Warning, TEXT("Code execution: %llu bytes"), MemoryProfiler.GetMemoryUsage());
}

