// Fill out your copyright notice in the Description page of Project Settings.


#include "PythonWriteTestActor.h"

APythonWriteTestActor::APythonWriteTestActor()
{
}

void APythonWriteTestActor::Test(int NumberOfActions)
{
	Super::Test(NumberOfActions);

	PyObject* main = PyImport_AddModule("__main__");
	PyObject* globalDictionary = PyModule_GetDict(main);
	PyObject* localDictionary = PyDict_New();
	
	// Time
	{
		for (int index = 0; index < NumberOfActions; index++)
		{
			TimerProfiler TimerProfiler;
			TimerProfiler.Start();

			const char* pythonScript = "a = b\n";
			PyDict_SetItemString(localDictionary, "b", PyFloat_FromDouble(1));
			PyRun_String(pythonScript, Py_file_input, globalDictionary, localDictionary);
			
			TimerProfiler.Stop();

			TimerResults.Add(TimerProfiler.GetDuration());
		}
	}

	// {
	// 	for (int index = 0; index < NumberOfActions; index++)
	// 	{
	// 		MemoryProfiler MemoryProfiler;
	// 		MemoryProfiler.Start();
	//
	// 		const char* pythonScript = "a = b\n";
	// 		PyDict_SetItemString(localDictionary, "b", PyFloat_FromDouble(1));
	// 		PyRun_String(pythonScript, Py_file_input, globalDictionary, localDictionary);
	// 		
	// 		MemoryProfiler.Stop();
	//
	// 		MemoryResults.Add(MemoryProfiler.GetMemoryUsage());
	// 	}
	// }
}

void APythonWriteTestActor::WriteVariableToPython()
{
}
