// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnableTestActor.h"

#include "ATProject/TestFramework/TimerProfiler.h"

// Sets default values
ASpawnableTestActor::ASpawnableTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnableTestActor::BeginPlay()
{
	Super::BeginPlay();
	SetupTestEnvironment();
	TestStartDelegate.Broadcast();
}

void ASpawnableTestActor::Destroyed()
{
	Super::Destroyed();
}

void ASpawnableTestActor::SetupTestEnvironment()
{
}

void ASpawnableTestActor::BreakdownTestEnvironment()
{
}

// Called every frame
void ASpawnableTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("[%s]RUN: %d"), *TestDescriptor, CurrentAmountOfActions);
	
	if (CurrentAmountOfActions < AmountOfActions)
	{
		TimerProfiler TimerProfiler;
		TimerProfiler.Start();
		DoTick(DeltaTime);
		TimerProfiler.Stop();

		const float FPS = 1.0f/DeltaTime;
		FPSResults.Add(FPS);
		CheckFPS(FPS);
		CheckTime(TimerProfiler.GetDuration());
		TimerResults.Add(TimerProfiler.GetDuration());
		CurrentAmountOfActions++;
	}
	else
	{
		CalculateAverages();
		BreakdownTestEnvironment();
		TestDoneDelegate.Broadcast(AverageTimerResult, AverageFPSResult, HighestFPSMeasured, LowestFPSMeasured, HighestTimeMeasured, LowestTimeMeasured);
	}
	
}

void ASpawnableTestActor::DoTick(float DeltaTime)
{
}

void ASpawnableTestActor::CalculateAverages()
{
	float TotalTime = 0;
	float TotalFPS = 0;

	for (const float Time : TimerResults)
	{
		TotalTime += Time;
	}

	for (const float FPS : FPSResults)
	{
		TotalFPS += FPS;
	}

	if (TotalTime != 0)
	{
		AverageTimerResult = TotalTime / TimerResults.Num();
	}

	if (TotalFPS != 0)
	{
		AverageFPSResult = TotalFPS / FPSResults.Num();
	}
}

void ASpawnableTestActor::CheckFPS(const float FPS)
{
	if (FPS > HighestFPSMeasured)
		HighestFPSMeasured = FPS;

	if (LowestFPSMeasured == 0 || FPS < LowestFPSMeasured)
		LowestFPSMeasured = FPS;
}

void ASpawnableTestActor::CheckTime(const float Time)
{
	if (Time > HighestTimeMeasured)
		HighestTimeMeasured = Time;

	if (LowestTimeMeasured == 0 || Time < LowestTimeMeasured)
		LowestTimeMeasured = Time;
}

