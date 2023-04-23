// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnableTestActor.h"

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
	TestStartDelegate.Broadcast();
}

void ASpawnableTestActor::Destroyed()
{
	Super::Destroyed();
}

// Called every frame
void ASpawnableTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("RUN: %d"), CurrentAmountOfActions);
	
	if (CurrentAmountOfActions < AmountOfActions)
	{
		DoTick(DeltaTime);
		CurrentAmountOfActions++;
	}
	else
	{
		CalculateAverages();
		TestDoneDelegate.Broadcast(AverageTimerResult, AverageFPSResult);
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

