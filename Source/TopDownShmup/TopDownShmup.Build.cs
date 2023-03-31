// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TopDownShmup : ModuleRules
{
	public TopDownShmup(ReadOnlyTargetRules Target): base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AIModule" });
		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
