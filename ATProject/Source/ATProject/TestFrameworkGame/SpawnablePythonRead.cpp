// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnablePythonRead.h"

void ASpawnablePythonRead::BeginPlay()
{
	TestDescriptor = "PythonRead";
	Super::BeginPlay();
}

void ASpawnablePythonRead::SetupTestEnvironment()
{
	Py_Initialize();

	MainModule = PyImport_AddModule("__main__");
	GlobalDictionary = PyModule_GetDict(MainModule);
	LocalDictionary = PyDict_New();
	
	Super::SetupTestEnvironment();
}

void ASpawnablePythonRead::BreakdownTestEnvironment()
{
	Py_Finalize();
	MainModule = nullptr;
	GlobalDictionary = nullptr;
	LocalDictionary = nullptr;
	Super::BreakdownTestEnvironment();
}

void ASpawnablePythonRead::Tick(float DeltaSeconds)
{
	const char* pythonScript = "a = b\n";
	PyDict_SetItemString(LocalDictionary, "b", PyFloat_FromDouble(DeltaSeconds));
	PyRun_String(pythonScript, Py_file_input, GlobalDictionary, LocalDictionary);
	Super::Tick(DeltaSeconds);
}

void ASpawnablePythonRead::DoTick(float DeltaTime)
{
	double result = PyFloat_AsDouble(PyDict_GetItemString(LocalDictionary, "a"));
}
