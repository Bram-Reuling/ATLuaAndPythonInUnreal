using System.IO;
using UnrealBuildTool;

public class PythonLibrary : ModuleRules
{
	public PythonLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		if (Target.Platform != UnrealTargetPlatform.Win64) return;
		
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "x64", "Release", "python311.lib"));
		PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "x64", "Release", "python311.dll"));
		RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "x64", "Release", "python311.dll"));
	}
}