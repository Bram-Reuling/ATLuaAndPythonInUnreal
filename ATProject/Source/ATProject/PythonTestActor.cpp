// Fill out your copyright notice in the Description page of Project Settings.

#define PY_SSIZE_T_CLEAN

#include "PythonTestActor.h"

// Sets default values
APythonTestActor::APythonTestActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APythonTestActor::BeginPlay()
{
	Super::BeginPlay();

	ScriptFolderPath = FPaths::ProjectDir().Append("Scripts/Python/");
	FullScriptPath = ScriptFolderPath;
	FullScriptPath.Append(PythonScriptFileName).Append(".py");
	FullFilePath = TCHAR_TO_ANSI(*FullScriptPath);
	
	InitializePython();
	
	pModuleName = PyUnicode_FromString(TCHAR_TO_ANSI(*PythonScriptFileName));

	if (!pModuleName)
	{
		UE_LOG(LogTemp, Warning, TEXT("pModuleName == nullptr"))
	}
	
	pModule = PyImport_Import(pModuleName);
	if (!pModule) return;

	UE_LOG(LogTemp, Warning, TEXT("Python Module Loaded!"));

	for (FString function : PythonFunctions)
	{
		if (PyObject* pFunc = PyObject_GetAttrString(pModule, TCHAR_TO_ANSI(*function)))
		{
			UE_LOG(LogTemp, Warning, TEXT("Loaded function: %s"), *function);
			PythonFunctionObjects.Add(function, pFunc);
		}
	}
	
	if (PyObject* BeginPlayFunc = PythonFunctionObjects["PrintUnrealFromPython"])
	{
		PyObject_CallObject(BeginPlayFunc, nullptr);
	}
}

void APythonTestActor::Destroyed()
{
	UE_LOG(LogTemp, Log, TEXT("APythonTestActor::Destroyed"));
	Super::Destroyed();
	
	Py_Finalize();
}

// Called every frame
void APythonTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PyObject* TickFunc = PythonFunctionObjects["Tick"];
	if (pModule && TickFunc)
	{
		PyObject_CallObject(TickFunc, nullptr);
	}
}

#pragma region Python Code

// Python stuff
static PyObject* PGSPrintUnreal(PyObject *self, PyObject *args)
{
	UE_LOG(LogTemp, Log, TEXT("Called from Python!"));

	return nullptr;
}

static PyMethodDef PgsMethods[] = {
	{"PrintUnreal", PGSPrintUnreal, METH_VARARGS, "Print a string in Unreal Engine."},
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

void APythonTestActor::InitializePython()
{
	UE_LOG(LogTemp, Log, TEXT("APythonTestActor::InitializePythonModule"));

	PyImport_AppendInittab("pgs", &PyInit_pgs);
	
	Py_Initialize();

	PyRun_SimpleString("import sys");
	const FString sysPathAppendString = "sys.path.append('" + ScriptFolderPath + "')";
	PyRun_SimpleString(TCHAR_TO_ANSI(*sysPathAppendString));
	const FString sysArgString = "sys.argv = ['"+ PythonScriptFileName +".py']";
	PyRun_SimpleString(TCHAR_TO_ANSI(*sysArgString));
}

#pragma endregion 