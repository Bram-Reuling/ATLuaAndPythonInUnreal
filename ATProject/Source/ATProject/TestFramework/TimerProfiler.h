// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <chrono>

/**
 * Class that holds timer functionality and functionality to return the elapsed time in μs.
 */
class TimerProfiler
{
public:
	TimerProfiler();
	~TimerProfiler();

	// Starts the timer.
	void Start();

	// Stops the timer.
	void Stop();

	// Gets the duration of the timer in microseconds (μs).
	float GetDuration() const;

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> StartTimePoint;
	float Duration;
};
