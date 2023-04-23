// Fill out your copyright notice in the Description page of Project Settings.

#define PY_SSIZE_T_CLEAN

#include "SpawnablePythonMove.h"

#pragma region Python

static PyObject* PGSMoveActor(PyObject* self, PyObject* args)
{
	if (ASpawnablePythonMove* Actor = ASpawnablePythonMove::Instance)
	{
		UE_LOG(LogTemp, Warning, TEXT("PGSMoveActor: Actor Found!"));
		const FVector CurrentPosition = Actor->GetActorLocation();
		const FVector NewPosition = CurrentPosition + FVector::One();

		Actor->SetActorLocation(NewPosition);	
	}

	return nullptr;
}

static PyMethodDef PgsMethods[] = {
	{"MoveActor", PGSMoveActor, METH_VARARGS, "Print a string in Unreal Engine."},
	{nullptr, nullptr, 0, nullptr}
};

static PyModuleDef PgsModule = {
	PyModuleDef_HEAD_INIT, "pgs", nullptr, -1, PgsMethods,
	nullptr, nullptr, nullptr, nullptr
};

static PyObject* PyInit_pgs(void)
{
	return PyModule_Create(&PgsModule);
}

#pragma endregion 

void ASpawnablePythonMove::BeginPlay()
{
	TestDescriptor = "PythonMove";
	Instance = this;
	Super::BeginPlay();
}

void ASpawnablePythonMove::SetupTestEnvironment()
{
	PyImport_AppendInittab("pgs", &PyInit_pgs);
	
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

	if (PyObject* pFunc = PyObject_GetAttrString(pModule, "Tick"))
	{
		UE_LOG(LogTemp, Warning, TEXT("Loaded function: Tick"));
		pTickFunction = pFunc;
	}
	
	Super::SetupTestEnvironment();
}

void ASpawnablePythonMove::BreakdownTestEnvironment()
{
	Py_Finalize();
	pModuleName = nullptr;
	pModule = nullptr;
	pTickFunction = nullptr;
	Instance = nullptr;
	Super::BreakdownTestEnvironment();
}

void ASpawnablePythonMove::Tick(float DeltaSeconds)
{
	if (pModule && pTickFunction)
	{
		Super::Tick(DeltaSeconds);
	}
}

void ASpawnablePythonMove::DoTick(float DeltaTime)
{
	//PyObject* pArgs = PyTuple_New(1);
	//PyTuple_SetItem(pArgs, 0, PyFloat_FromDouble(DeltaTime));
	PyObject_CallObject(pTickFunction, nullptr);
}
