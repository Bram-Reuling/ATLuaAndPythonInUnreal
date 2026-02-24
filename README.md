# ATLuaAndPythonInUnreal
**Disclaimer**: I know that pushing dll files to GitHub is not good practice, but I did it in this case so you didnt have to search and download them for yourself. To make the project work, please copy the dll files from `Source/ThirdParty/LuaLibrary/x64/Release` and `Source/ThirdParty/PythonLibrary/x64/Release` into the `Binaries` folder of the project. I am also fully aware of the fact that Unreal Engine comes with Python already installed so I could have used that, but instead I went with importing my own because that is Python 3.11. The version included by Unreal Engine is Python 3.8.

<h1 align="center">Lua VS Python</h1>

## Brief Description
This wiki will talk about the embedding of scripting languages in Unreal Engine and we will compare the performance of two embedded languages: Lua and Python. The comparisons made in this document focus on the impact on FPS in a game scene and the execution times of the calls being made to the scripting languages from C++ and also from the scripting languages to C++.

Programming language embedding can be described as a process where a host language (in this case C++ or any other compiled language) will run another language (interpreted languages are the most common for this). For example: Unreal Engine uses Python to do editor scripting. Unreal Engine has embedded Python in C++ and exposes functions from C++ to Python but also requires the Python script that will be executed to implement a set of function which the engine can call.

This prototype uses C++ as its host language and Python and Lua as the embedded scripting languages. The prototype also includes a framework for writing game tests and running those tests automatically and retrieving the results from those tests.

**Evaluation Proposal:** Embed Lua and Python in Unreal Engine with C++ and compare the performance on tasks such as writing values to variables and moving game objects around through script and compare the difficulty of embedding and using the scripting languages.

**Relevance:**
Games also leverage the use of embedding languages into them which allows players to extend the games functionality by creating mods or addons. A good example of a game that uses an embedded scripting language is Garry's Mod which uses the language Lua (Pearson, Craig (29 August 2012). Furthermore, scripting languages are also used in game engines to make the development of games easier for for example designer that need to prototype functionality quickly. One of these engines is the engine for Quake that uses QuakeC which is an byte-compiled scripting language that can change behavior of objects during simulation (Lewis & Jacobson, 2002). Another game engine that uses a scripting language is the Unity Game Engine. Unity uses C# to create the logic for game objects and other logic for the games you build in that engine (Singh & Kaur, 2022).

**References:**
* Pearson, Craig (29 August 2012). ["A Brief History Of Garry's Mod: Count To Ten"](https://www.rockpapershotgun.com/2012/08/29/a-brief-history-of-garrys-mod-count-to-ten/). [Rock Paper Shotgun](https://en.wikipedia.org/wiki/Rock_Paper_Shotgun). [Archived](https://web.archive.org/web/20190727103421/https://www.rockpapershotgun.com/2012/08/29/a-brief-history-of-garrys-mod-count-to-ten/) from the original on 27 July 2019. Retrieved 23 April 2023.
* Lewis, & Jacobson. (2002, January). Game Engines in Scientific Research. Retrieved April 24, 2023, from https://www.cse.unr.edu/~sushil/class/gas/papers/GameAIp27-lewis.pdf
* Singh, & Kaur. (2022). Game Development using Unity Game Engine. Game Development Using Unity Game Engine | IEEE Conference Publication | IEEE Xplore. Retrieved April 24, 2023, from https://ieeexplore.ieee.org/stampPDF/getPDF.jsp?tp=&arnumber=10007155&ref=
* Python Foundation. (2023, April). 1. Embedding Python in Another Application. Embedding Python in Another Application. Retrieved April 24, 2023, from https://docs.python.org/3/extending/embedding.html
* OneLoneCoder. (2019, March 24). Embedding Lua in C++ #1 [Video]. YouTube. Retrieved April 24, 2023, from https://www.youtube.com/watch?v=4l5HdmPoynw

## Comparison
### Basic test setup
For the testing framework, I created a `SpawnableTestActor` class that every test will inherit from. This class comes with the base functionality for generating the time measurements and FPS measurements so that every class that inherits from this class does not have to call that logic anymore. The test will run in game so we are testing every Tick (Update). Every Tick we check if the amount of actions (action is for example a write to Lua or a function call to Python) that have run in the class and check if we went over the amount of actions that we want to be completed by the class. If it is less than the total that we want we will call another function called `DoTick`. The inheriting functions will implement the functions calls in this function. The `SpawnableTestActor` class will start the timer before calling the `DoTick` function and stop it afterwards. It will then gather the results and put them into an array.

```c++
// Called every frame
void ASpawnableTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UE_LOG(LogTemp, Warning, TEXT("[%s]RUN: %d"), *TestDescriptor, CurrentAmountOfActions);
	
	if (CurrentAmountOfActions < AmountOfActions)
	{
		TimerProfiler TimerProfiler;
		TimerProfiler.Start();
		DoTick(DeltaTime);
		TimerProfiler.Stop();

		const float FPS = 1.0f/DeltaTime;
		FPSResults.Add(FPS);
		CheckFPS(FPS);
		CheckTime(TimerProfiler.GetDuration());
		TimerResults.Add(TimerProfiler.GetDuration());
		CurrentAmountOfActions++;
	}
	else
	{
		CalculateAverages();
		BreakdownTestEnvironment();
		TestDoneDelegate.Broadcast(AverageTimerResult, AverageFPSResult, HighestFPSMeasured, LowestFPSMeasured, HighestTimeMeasured, LowestTimeMeasured);
	}
	
}
```

### Writing & Reading operations
The first test was writing to a variable and reading from one in Lua and Python in a running scene. The output of all the tests will be in FPS with a max, average and min result per action for impact on performance and in microseconds for code execution time with a max, average and min per action.

The following code was run in the `DoTick` function during the test:

```c++
// Python - Write
const char* pythonScript = "a = b\n";
PyDict_SetItemString(LocalDictionary, "b", PyFloat_FromDouble(1)); // PyInt_FromInt was not a thing anymore so I used this.
PyRun_String(pythonScript, Py_file_input, GlobalDictionary, LocalDictionary);

// Python - Read
double result = PyFloat_AsDouble(PyDict_GetItemString(LocalDictionary, "a")); // CPython did not have any class supporting integers for some reason so I am using this.

// Lua - Write
const char* CharacterCommand = "a = 1";
luaL_dostring(Lua_State, CharacterCommand)

//Lua - Read
lua_getglobal(Lua_State, "a");
if (lua_isnumber(Lua_State, -1))
{
	float a = (float)lua_tonumber(Lua_State, -1);
}
```

<img src="https://raw.githubusercontent.com/Bram-Reuling/ATLuaAndPythonInUnreal/main/Measurements/WriteFPS.png" width="600" />
<img src="https://raw.githubusercontent.com/Bram-Reuling/ATLuaAndPythonInUnreal/main/Measurements/WriteTime.png" width="600" />
<img src="https://raw.githubusercontent.com/Bram-Reuling/ATLuaAndPythonInUnreal/main/Measurements/ReadFPS.png" width="600" />
<img src="https://raw.githubusercontent.com/Bram-Reuling/ATLuaAndPythonInUnreal/main/Measurements/ReadTime.png" width="600" />

If we look to the impact from the calls on the FPS of the game we can see that Lua on average is 12.5 percent lower than a Python write action. In the read action the FPS of Lua is on average 14 percent lower than the FPS that we have when running Python code. This can be caused by Lua taking in a pointer to the Lua state created in the actor class while Python holds the state itself and does not require you to pass in a state that you created. Meanwhile if we take a look on the execution time per write and read we can see that on average Lua is faster than Python with on average per write action 66 percent and on the read action 6 percent. The reason that I can think of why Lua is much faster in execution time is because the language is more compact than Python.

So if you would go for impact on FPS, Python is a clear winner here on both read and write and Lua will be the clear winner of the execution time. 

### Function Calls
The first test was writing to a variable and reading from one in Lua and Python in a running scene. The output of all the tests will be in FPS with a max, average and min result per action for impact on performance and in microseconds for code execution time with a max, average and min per action.

The following code was called from C++ during the test:

Python:
```python
def add(a, b):
    return a + b

import pgs # Module created in C++

def Tick():
    pgs.MoveActor() # C++ function exposed to Python
```

Lua:
```lua
function add(a, b)
    return a + b
end

function Tick()
    MoveActor() -- Function exposed from C++
end
```
For detailed implementations go to the folder `Source/ATProject/TestFrameworkGame/` and check `SpawnableLuaAdd or Move.cpp` and `SpawnablePythonAdd or Move.cpp`.

#### Add Function
<img src="https://raw.githubusercontent.com/Bram-Reuling/ATLuaAndPythonInUnreal/main/Measurements/AddFPS.png" width="600" />
<img src="https://raw.githubusercontent.com/Bram-Reuling/ATLuaAndPythonInUnreal/main/Measurements/AddTime.png" width="600" />

#### Move Actor Function
<img src="https://raw.githubusercontent.com/Bram-Reuling/ATLuaAndPythonInUnreal/main/Measurements/MoveActorFPS.png" width="600" />
<img src="https://raw.githubusercontent.com/Bram-Reuling/ATLuaAndPythonInUnreal/main/Measurements/MoveActorTime.png" width="600" />

#### Function conclusion
As you can see in the above graphs the differences of the FPS measurements are really small between Lua and Python. During the add calls, Python had a better average FPS and during the move actor calls they had the same average on the FPS part. 

On the execution time part, Lua was the fastest in both tests on all stats (min, average and max).

On the performance impact part there is no clear winner but on the execution time part Lua won.

### Difficulty of embedding
Embedding both languages in Unreal Engine is a bit of a hassle because you need to setup a special directory structure for including ThirdParty software in Unreal Engine. If you have that folder structure (`Source/ThirdParty/LibraryX`) you only need to add the include files to that directory and create a Build.cs file that handles loading the dll files the library has. For the dll files to be picked up by the engine, you need to manually copy them to the `Binaries` folder in the project root. After that has been setup, you need to include the libraries in the Build.cs file of the project source directory to use the libraries. 

To write a variable to Lua, you first need to create a Lua state that will be used to execute whatever you want Lua to do. After that you make a string that will be the command and you call the `luaL_dostring` macro where you pass in that string you just created. Final code looks like this:

```c++
lua_State* Lua_State = luaL_newstate();

if (Lua_State == nullptr)
{
	UE_LOG(LogTemp, Error, TEXT("Lua_State == nullptr"));
	return;
}

luaL_openlibs(Lua_State);

const char* CharacterCommand = "a = 1";

if (luaL_dostring(Lua_State, CharacterCommand) != LUA_OK)
{
	UE_LOG(LogTemp, Warning, TEXT("luaL_dostring != LUA_OK"));
}

lua_close(Lua_State);
```

To write a variable to Python you first need to initialize the Python interpreter, add the main module to the interpreter so Python knows where to put that variable, create a global and a local dictionary to put the variable in, create a string that sets `a` to be `b` and set `b` by calling the `SetItemString` function and then run the string with the global and local dictionary.

Final code looks like this:

```c++
Py_Initialize();
PyObject* MainModule = PyImport_AddModule("__main__");
PyObject* GlobalDictionary = PyModule_GetDict(MainModule);
PyObject* LocalDictionary = PyDict_New();

const char* pythonScript = "a = b\n";
PyDict_SetItemString(LocalDictionary, "b", PyFloat_FromDouble(1));
PyRun_String(pythonScript, Py_file_input, GlobalDictionary, LocalDictionary);
Py_Finalize();
```

**NOTE: I omitted all the error checking to make the examples easier.**

As a conclusion, I found that implementing Lua into C++ was way easier than Python because there are actually good tutorials for implementing Lua into C++. The CPython API that comes with the Python installer had less of good documentation on how to do things but I managed to get everything I wanted working in the end.

## Conclusion
If you are looking to use Python or Lua for game scripting than according to the results Python would be better for FPS performance but Lua will be better on execution time. From what I could find online, the general time complexity of both the Lua embed and Python embed in C++ is constant or **O(1)**.
