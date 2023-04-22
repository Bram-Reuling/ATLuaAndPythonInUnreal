// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryProfiler.h"

bool MemoryProfiler::Start()
{
	const HANDLE CurrentProcess = GetCurrentProcess();
	if(!GetProcessMemoryInfo(CurrentProcess, &StartMemoryInfo, sizeof(StartMemoryInfo)))
	{
		return false;
	}

	return true;
}

bool MemoryProfiler::End()
{
	const HANDLE CurrentProcess = GetCurrentProcess();
	if(!GetProcessMemoryInfo(CurrentProcess, &EndMemoryInfo, sizeof(EndMemoryInfo)))
	{
		return false;
	}

	return true;
}

SIZE_T MemoryProfiler::GetMemoryUsage() const
{
	const SIZE_T StartMemory = StartMemoryInfo.WorkingSetSize;
	const SIZE_T EndMemory = EndMemoryInfo.WorkingSetSize;
	return EndMemory - StartMemory;
}
