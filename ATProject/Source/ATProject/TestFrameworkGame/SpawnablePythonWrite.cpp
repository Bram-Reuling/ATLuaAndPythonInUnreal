// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnablePythonWrite.h"

void ASpawnablePythonWrite::BeginPlay()
{
	TestDescriptor = "PythonWrite";
	Super::BeginPlay();
}

void ASpawnablePythonWrite::SetupTestEnvironment()
{
	Py_Initialize();

	MainModule = PyImport_AddModule("__main__");
	GlobalDictionary = PyModule_GetDict(MainModule);
	LocalDictionary = PyDict_New();
	
	Super::SetupTestEnvironment();
}

void ASpawnablePythonWrite::BreakdownTestEnvironment()
{
	Py_Finalize();
	MainModule = nullptr;
	GlobalDictionary = nullptr;
	LocalDictionary = nullptr;
	Super::BreakdownTestEnvironment();
}

void ASpawnablePythonWrite::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ASpawnablePythonWrite::DoTick(float DeltaTime)
{
	const char* pythonScript = "a = b\n";
	PyDict_SetItemString(LocalDictionary, "b", PyFloat_FromDouble(DeltaTime));
	PyRun_String(pythonScript, Py_file_input, GlobalDictionary, LocalDictionary);
}
