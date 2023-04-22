// Fill out your copyright notice in the Description page of Project Settings.


#include "TestManager.h"

// Sets default values
ATestManager::ATestManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATestManager::BeginPlay()
{
	Super::BeginPlay();
	RunSample();
}

void ATestManager::RunSample()
{
	if (TestActors.IsEmpty()) return;

	if (!CurrentTestActor)
	{
		ABaseTestActor* TestActor = Cast<ABaseTestActor>(TestActors[CurrentTestActorIndex]);
		if (!TestActor) return;

		CurrentTestActor = TestActor;

		CurrentTestActor->TestStartDelegate.AddUniqueDynamic(this, &ATestManager::SampleRunStartEvent);
		CurrentTestActor->TestDoneDelegate.AddUniqueDynamic(this, &ATestManager::SampleRunDoneEvent);
	}

	UE_LOG(LogTemp, Warning, TEXT("TestActor found!"))

	CurrentTestActor->PerformTest(Actions);
}

void ATestManager::SampleRunStartEvent()
{
	CurrentSampleRun++;
	UE_LOG(LogTemp, Warning, TEXT("Starting sample run %d of actor index %d with descriptor: %s"), CurrentSampleRun, CurrentTestActorIndex, *CurrentTestActor->GetTestDescriptor());
}

void ATestManager::SampleRunDoneEvent()
{
	UE_LOG(LogTemp, Warning, TEXT("Finished sample run %d of actor index %d with descriptor: %s"), CurrentSampleRun, CurrentTestActorIndex, *CurrentTestActor->GetTestDescriptor());

	CurrentTestActor->CalculateAverages();
	
	CurrentTestTimerResults.Add(CurrentTestActor->GetAverageTimerResult());
	CurrentTestMemoryResults.Add(CurrentTestActor->GetAverageMemoryResult());
	CurrentTestFPSResults.Add(CurrentTestActor->GetAverageFPSResult());
	
	if (CurrentSampleRun == Samples)
	{
		CalculateAndDisplayAverage();
		if (CurrentTestActorIndex + 1 == TestActors.Num()) return;
		CurrentTestActor->TestStartDelegate.Clear();
		CurrentTestActor->TestDoneDelegate.Clear();
		CurrentTestActor = nullptr;
		CurrentTestActorIndex++;

		CurrentTestTimerResults.Empty();
		CurrentTestMemoryResults.Empty();
		CurrentTestFPSResults.Empty();

		CurrentSampleRun = 0;
	}

	// Run the next sample.
	RunSample();
}

void ATestManager::CalculateAndDisplayAverage()
{
	float TotalTime = 0;
	float TotalMemory = 0;
	float TotalFPS = 0;

	for (const long long Time : CurrentTestTimerResults)
	{
		TotalTime += Time;
	}

	for (const SIZE_T Memory : CurrentTestMemoryResults)
	{
		TotalMemory += Memory;
	}

	for (const float FPS : CurrentTestFPSResults)
	{
		TotalFPS += FPS;
	}

	if (TotalTime == 0 || TotalMemory == 0 || TotalFPS == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("==================RESULT OF %s TEST=================="), *CurrentTestActor->GetTestDescriptor());
		UE_LOG(LogTemp, Warning, TEXT("TotalTime: %f μs"), TotalTime);
		UE_LOG(LogTemp, Warning, TEXT("TotalMemory: %f bytes"), TotalMemory);
		UE_LOG(LogTemp, Warning, TEXT("TotalFPS: %f FPS"), TotalFPS);
		UE_LOG(LogTemp, Warning, TEXT("======================================================="));
		return;	
	}
	
	const float AverageTimerResult = TotalTime / Actions;
	const float AverageMemoryResult = TotalMemory / Actions;
	const float AverageFPSResult = TotalFPS / Actions;

	UE_LOG(LogTemp, Warning, TEXT("==================RESULT OF %s TEST=================="), *CurrentTestActor->GetTestDescriptor());
	UE_LOG(LogTemp, Warning, TEXT("AverageTimerResult: %f μs"), AverageTimerResult);
	UE_LOG(LogTemp, Warning, TEXT("AverageMemoryResult: %f bytes"), AverageMemoryResult);
	UE_LOG(LogTemp, Warning, TEXT("AverageFPSResult: %f FPS"), AverageFPSResult);
	UE_LOG(LogTemp, Warning, TEXT("====================================================="));
}

