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
	//CurrentTestFPSResults.Add(CurrentTestActor->GetAverageFPSResult());
	
	if (CurrentSampleRun == Samples)
	{
		CalculateAverage();
		if (CurrentTestActorIndex + 1 == TestActors.Num())
		{
			DisplayResults();
			return;
		}
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

void ATestManager::CreateResult(float TotalTime, float TotalMemory, float TotalFPS)
{
	FResult Result;
	Result.ActorIndex = CurrentTestActorIndex;
	Result.TestDescriptor = CurrentTestActor->GetTestDescriptor();
	Result.TimerResult = TotalTime;
	Result.MemoryResult = TotalMemory;
	Result.FPSResult = TotalFPS;

	Results.Add(Result);
}

void ATestManager::CalculateAverage()
{
	float TotalTime = 0;
	float TotalMemory = 0;
	float TotalFPS = 0;

	for (const float Time : CurrentTestTimerResults)
	{
		TotalTime += Time;
	}

	for (const SIZE_T Memory : CurrentTestMemoryResults)
	{
		TotalMemory += Memory;
	}

	for (const float FPS : CurrentTestFPSResults)
	{
		//TotalFPS += FPS;
	}

	UE_LOG(LogTemp, Warning, TEXT("Total Time: %f"), TotalTime);
	UE_LOG(LogTemp, Warning, TEXT("Total Memory: %f"), TotalMemory);
	
	if (TotalTime == 0 || TotalMemory == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("NO VALID TEST RESULTS"));
		CreateResult(0,0,0);
		return;	
	}
	
	const float AverageTimerResult = TotalTime / CurrentTestTimerResults.Num();
	const float AverageMemoryResult = TotalMemory / CurrentTestMemoryResults.Num();
	//const float AverageFPSResult = TotalFPS / Actions;

	CreateResult(AverageTimerResult / 1000, AverageMemoryResult, 0);
}

void ATestManager::DisplayResults()
{
	for(FResult Result : Results)
	{
		UE_LOG(LogTemp, Warning, TEXT("==================RESULT OF %s TEST=================="), *Result.TestDescriptor);
		UE_LOG(LogTemp, Warning, TEXT("AverageTimerResult: %f μs"), Result.TimerResult);
		UE_LOG(LogTemp, Warning, TEXT("AverageMemoryResult: %f bytes"), Result.MemoryResult);
		UE_LOG(LogTemp, Warning, TEXT("AverageFPSResult: %f FPS"), Result.FPSResult);
		UE_LOG(LogTemp, Warning, TEXT("======================================================="));
	}
}

