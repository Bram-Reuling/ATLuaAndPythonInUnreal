// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerProfiler.h"

TimerProfiler::TimerProfiler(): Duration(0)
{
}

TimerProfiler::~TimerProfiler() {}

void TimerProfiler::Start()
{
	StartTimePoint = std::chrono::high_resolution_clock::now();
}

void TimerProfiler::Stop()
{
	const std::chrono::time_point<std::chrono::high_resolution_clock> endTimePoint = std::chrono::high_resolution_clock::now();

	const long long Start = std::chrono::time_point_cast<std::chrono::nanoseconds>(StartTimePoint).time_since_epoch().count();
	const long long End = std::chrono::time_point_cast<std::chrono::nanoseconds>(endTimePoint).time_since_epoch().count();

	Duration = End - Start;
}

float TimerProfiler::GetDuration() const
{
	return Duration;
}
