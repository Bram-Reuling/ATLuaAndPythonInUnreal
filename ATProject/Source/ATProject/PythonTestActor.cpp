// Fill out your copyright notice in the Description page of Project Settings.

#define PY_SSIZE_T_CLEAN

#include "PythonTestActor.h"
#include "PythonLibrary/Python.h"

// Python stuff
static PyObject* emb_printunreal(PyObject *self, PyObject *args)
{
	UE_LOG(LogTemp, Log, TEXT("Called from Python!"));

	return nullptr;
}

static PyMethodDef EmbMethods[] = {
	{"printunreal", emb_printunreal, METH_VARARGS, "Print a string in Unreal Engine."},
	{nullptr, nullptr, 0, nullptr}
};

static PyModuleDef EmbModule = {
	PyModuleDef_HEAD_INIT, "emb", nullptr, -1, EmbMethods,
	nullptr, nullptr, nullptr, nullptr
};

static PyObject* PyInit_emb(void)
{
	return PyModule_Create(&EmbModule);
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

	PyImport_AppendInittab("emb", &PyInit_emb);
	
	Py_Initialize();

	const char* file = TCHAR_TO_ANSI(*RelativePath);
	FILE* PScriptFile = fopen(file, "r");
	if(PScriptFile)
	{
		PyRun_SimpleFile(PScriptFile, "script.py");
		fclose(PScriptFile);
	}
	
	Py_Finalize();
}

// Called every frame
void APythonTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

