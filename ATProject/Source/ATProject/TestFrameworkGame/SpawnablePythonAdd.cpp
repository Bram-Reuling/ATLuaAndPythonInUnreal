// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnablePythonAdd.h"

void ASpawnablePythonAdd::BeginPlay()
{
	TestDescriptor = "PythonAdd";
	Super::BeginPlay();
}

void ASpawnablePythonAdd::SetupTestEnvironment()
{
	Py_Initialize();
	
	ScriptFolderPath = FPaths::ProjectDir().Append("Scripts/Python/");
	FullScriptPath = ScriptFolderPath;
	FullScriptPath.Append(PythonScriptFileName).Append(".py");
	FullFilePath = TCHAR_TO_ANSI(*FullScriptPath);

	PyRun_SimpleString("import sys");
	const FString sysPathAppendString = "sys.path.append('" + ScriptFolderPath + "')";
	PyRun_SimpleString(TCHAR_TO_ANSI(*sysPathAppendString));
	const FString sysArgString = "sys.argv = ['"+ PythonScriptFileName +".py']";
	PyRun_SimpleString(TCHAR_TO_ANSI(*sysArgString));

	pModuleName = PyUnicode_FromString(TCHAR_TO_ANSI(*PythonScriptFileName));

	if (!pModuleName)
	{
		UE_LOG(LogTemp, Warning, TEXT("pModuleName == nullptr"))
	}

	pModule = PyImport_Import(pModuleName);
	if (!pModule) return;

	UE_LOG(LogTemp, Warning, TEXT("Python Module Loaded!"));

	if (PyObject* pFunc = PyObject_GetAttrString(pModule, "add"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Loaded function: add"));
		pAddFunction = pFunc;
	}
	
	Super::SetupTestEnvironment();
}

void ASpawnablePythonAdd::BreakdownTestEnvironment()
{
	Py_Finalize();
	pModuleName = nullptr;
	pModule = nullptr;
	pAddFunction = nullptr;
	Super::BreakdownTestEnvironment();
}

void ASpawnablePythonAdd::Tick(float DeltaSeconds)
{
	if (pModule && pAddFunction)
	{
		Super::Tick(DeltaSeconds);	
	}
}

void ASpawnablePythonAdd::DoTick(float DeltaTime)
{
	PyObject* pArgs = PyTuple_New(2);
	PyTuple_SetItem(pArgs, 0, PyFloat_FromDouble(DeltaTime));
	PyTuple_SetItem(pArgs, 1, PyFloat_FromDouble(20));
	if (const PyObject* pResult = PyObject_CallObject(pAddFunction, pArgs); pResult == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Cant add"));
	}
}
