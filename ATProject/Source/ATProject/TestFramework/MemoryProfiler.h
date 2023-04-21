// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <Windows.h>
#include <Psapi.h>

/**
 * 
 */
class ATPROJECT_API MemoryProfiler
{
public:
	MemoryProfiler();
	~MemoryProfiler();

	void Start();
	void End();
	SIZE_T GetMemoryUsage() const;

private:
	PROCESS_MEMORY_COUNTERS StartMemoryInfo;
	PROCESS_MEMORY_COUNTERS EndMemoryInfo;
};
