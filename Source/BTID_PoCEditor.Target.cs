// Copyright Misiaczki IRGK_WSEI

using UnrealBuildTool;
using System.Collections.Generic;

public class BTID_PoCEditorTarget : TargetRules
{
	public BTID_PoCEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "BTID_PoC" } );
	}
}
