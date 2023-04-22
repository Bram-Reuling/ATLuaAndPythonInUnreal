// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MemoryProfiler.h"
#include "TimerProfiler.h"
#include "BaseTestActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTestCaseStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTestCaseDone);

UENUM(BlueprintType)
enum ETestType
{
	Timer,
	Memory,
	FPS
};

UCLASS()
class ATPROJECT_API ABaseTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseTestActor();

protected:
#pragma region Settings
	
	ETestType TestType = ETestType::Timer;

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	FString TestDescriptor = "Base";
	
	int NumberOfActions = 0;

#pragma endregion 

#pragma region Results
	
	TArray<long long> TimerResults = {};
	TArray<SIZE_T> MemoryResults = {};
	TArray<float> FPSResults = {};

	long long AverageTimerResult = 0;
	SIZE_T AverageMemoryResult = 0;
	float AverageFPSResult = 0;

#pragma endregion 

#pragma region Setup & Breakdown
	
	// Function that sets up the language specific environment.
	virtual void SetupTestEnvironment();

	// Shuts the language specific environment down.
	virtual void BreakdownTestEnvironment();

#pragma endregion 

public:
#pragma region Getters & Setters
	
	void SetTestType(ETestType Type);
	ETestType GetTestType() const;

	long long GetAverageTimerResult() const;
	SIZE_T GetAverageMemoryResult() const;
	float GetAverageFPSResult() const;

	FString GetTestDescriptor() const;

#pragma endregion 

#pragma region TestFunctions
	
	// Actual test logic goes in here.
	virtual void PerformTest(int NumberOfAction);

	void CalculateAverages();

#pragma endregion 

#pragma region Delegates
	
	// Delegate for letting test manager know when the test starts.
	UPROPERTY()
	FTestCaseStart TestStartDelegate;

	UPROPERTY()
	// Delegate for letting test manager know when the test is done.
	FTestCaseDone TestDoneDelegate;

#pragma endregion 
};
