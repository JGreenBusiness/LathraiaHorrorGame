// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LathraiaHorrorUProjEditor : ModuleRules
{
	public LathraiaHorrorUProjEditor(ReadOnlyTargetRules Target) : base(Target)
	{
        PublicIncludePaths.AddRange(new string[] {
            "LathraiaHorrorUProjEditor/Public"
        });

        PrivateIncludePaths.AddRange(new string[] {
            "LathraiaHorrorUProjEditor/Private"
        });

        PublicDependencyModuleNames.AddRange(new string[] {
			"LathraiaHorrorUProj"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {
            "Core", 
			"CoreUObject", 
			"Engine",
            "UnrealEd"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
