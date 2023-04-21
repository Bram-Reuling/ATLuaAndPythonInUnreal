// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryProfiler.h"

MemoryProfiler::MemoryProfiler(): StartMemoryInfo(), EndMemoryInfo()
{
}

MemoryProfiler::~MemoryProfiler() {}

void MemoryProfiler::Start()
{
	const HANDLE CurrentProcess = GetCurrentProcess();
	GetProcessMemoryInfo(CurrentProcess, &StartMemoryInfo, sizeof(StartMemoryInfo));
}

void MemoryProfiler::End()
{
	const HANDLE CurrentProcess = GetCurrentProcess();
	GetProcessMemoryInfo(CurrentProcess, &EndMemoryInfo, sizeof(EndMemoryInfo));
}

SIZE_T MemoryProfiler::GetMemoryUsage() const
{
	const SIZE_T StartMemory = StartMemoryInfo.WorkingSetSize;
	const SIZE_T EndMemory = EndMemoryInfo.WorkingSetSize;
	return EndMemory - StartMemory;
}
