// Fill out your copyright notice in the Description page of Project Settings.

#define PY_SSIZE_T_CLEAN

#include "PythonTestActor.h"
#include "PythonLibrary/Python.h"

// PGS = Python Game Scripting

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

	UE_LOG(LogTemp, Log, TEXT("Running Python..."));

	FString RelativePath = FPaths::ProjectDir();

	RelativePath.Append("Scripts/Python/script.py");
	
	UE_LOG(LogTemp, Log, TEXT("RelativePath: %s"), *RelativePath);

	if (!FPaths::FileExists(RelativePath))
	{
		UE_LOG(LogTemp, Error, TEXT("File does not exist!"));
		return;
	}

	PyImport_AppendInittab("pgs", &PyInit_pgs);
	
	Py_Initialize();

	const char* file = TCHAR_TO_ANSI(*RelativePath);
	FILE* PScriptFile = fopen(file, "r");
	if(PScriptFile)
	{
		//PyRun_SimpleFile(PScriptFile, "script.py");
		fclose(PScriptFile);
	}

	PyRun_SimpleString("import sys");
	PyRun_SimpleString("sys.path.append('../../../../Projects/AT/ATProject/Scripts/Python/')");
	PyRun_SimpleString("sys.argv = ['script.py']");

	PyObject* pName = nullptr;
	PyObject* pModule = nullptr;
	PyObject* pFunc = nullptr;
	pName = PyUnicode_FromString("script");
	pModule = PyImport_Import(pName);
	if (pModule == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("pModule == nullptr"));	
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("eyy"));	
		pFunc = PyObject_GetAttrString(pModule, "PrintUnrealFromPython");
		PyObject_CallObject(pFunc, nullptr);
	}
	
	Py_Finalize();
}

// Called every frame
void APythonTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

