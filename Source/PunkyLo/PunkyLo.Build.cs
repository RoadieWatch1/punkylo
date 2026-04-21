// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PunkyLo : ModuleRules
{
	public PunkyLo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"PunkyLo",
			"PunkyLo/Core",
			"PunkyLo/Core/Subsystems",
			"PunkyLo/Player",
			"PunkyLo/Game"
		});
	}
}
