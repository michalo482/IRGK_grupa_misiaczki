// Copyright Misiaczki IRGK_WSEI

using UnrealBuildTool;
using System.Collections.Generic;

public class BTID_PoCTarget : TargetRules
{
	public BTID_PoCTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "BTID_PoC" } );
	}
}
