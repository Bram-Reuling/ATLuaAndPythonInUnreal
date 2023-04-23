// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTestActor.h"
#include "GameFramework/Actor.h"
#include "TestManager.generated.h"

USTRUCT(BlueprintType)
struct FGameTestResult
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ActorIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TestDescriptor = "";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimerResult = 0;

	UPROPERTY()
	float MemoryResult = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FPSResult = 0;
};

UCLASS()
class ATPROJECT_API ATestManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Number of times to run the test per test actor.
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int Samples = 100;

	// Number of actions per test.
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int Actions = 1000000;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TArray<AActor*> TestActors;

	int CurrentSampleRun = 0;
	int CurrentTestActorIndex = 0;

	UPROPERTY()
	ABaseTestActor* CurrentTestActor = nullptr;

	TArray<float> CurrentTestTimerResults = {};
	TArray<SIZE_T> CurrentTestMemoryResults = {};
	TArray<float> CurrentTestFPSResults = {};

	TArray<FGameTestResult> Results = {};

	void RunSample();
	
	UFUNCTION()
	void SampleRunStartEvent();

	UFUNCTION()
	void SampleRunDoneEvent();
	void CreateResult(float TotalTime, float TotalMemory, float TotalFPS);
	void CalculateAverage();
	void DisplayResults();
};
