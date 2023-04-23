// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnableTestActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameTestCaseStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FGameTestCaseDone, float, ResultOfTimer, float, ResultOfFPS, float, FPSHigh, float, FPSLow);

UCLASS()
class ATPROJECT_API ASpawnableTestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnableTestActor();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	virtual void SetupTestEnvironment();
	virtual void BreakdownTestEnvironment();

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	FString TestDescriptor = "Base";

	UPROPERTY(EditAnywhere, meta=(AllowPrivateAccess="true"))
	int AmountOfActions = 100;

	int CurrentAmountOfActions = 0;

	TArray<float> TimerResults = {};
	TArray<float> FPSResults = {};

	float AverageTimerResult = 0;
	float AverageFPSResult = 0;

	float HighestFPSMeasured = 0;
	float LowestFPSMeasured = 0;

	void CalculateAverages();

	void CheckFPS(const float FPS);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void DoTick(float DeltaTime);

	// Delegate for letting test manager know when the test starts.
	UPROPERTY(BlueprintAssignable)
	FGameTestCaseStart TestStartDelegate;

	UPROPERTY(BlueprintAssignable)
	// Delegate for letting test manager know when the test is done.
	FGameTestCaseDone TestDoneDelegate;

	UFUNCTION(BlueprintCallable)
	FString GetDescriptor() const {return TestDescriptor;}
};
