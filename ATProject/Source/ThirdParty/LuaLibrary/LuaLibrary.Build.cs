using System.IO;
using UnrealBuildTool;

public class LuaLibrary : ModuleRules
{
	public LuaLibrary(ReadOnlyTargetRules Target) : base(Target)
	{
		Type = ModuleType.External;

		if (Target.Platform != UnrealTargetPlatform.Win64) return;
		
		PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "x64", "Release", "liblua54.a"));
		PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "x64", "Release", "lua54.dll"));
		RuntimeDependencies.Add(Path.Combine(ModuleDirectory, "x64", "Release", "lua54.dll"));
	}
}