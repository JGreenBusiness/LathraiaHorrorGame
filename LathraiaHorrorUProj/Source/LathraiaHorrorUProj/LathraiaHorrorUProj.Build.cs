// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LathraiaHorrorUProj : ModuleRules
{
	public LathraiaHorrorUProj(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		
		PublicIncludePaths.AddRange(new string[] {
			"LathraiaHorrorUProj",
			"LathraiaHorrorUProj/AI",
			"LathraiaHorrorUProj/AI/Tasks",
			"LathraiaHorrorUProj/AI/Decorators"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
