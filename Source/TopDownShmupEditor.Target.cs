// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class TopDownShmupEditorTarget : TargetRules
{
	public TopDownShmupEditorTarget(TargetInfo Target): base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.AddRange( new string[] { "TopDownShmup" } );
	}

	
}
