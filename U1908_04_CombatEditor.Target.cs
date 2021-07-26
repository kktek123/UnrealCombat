// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class U1908_04_CombatEditorTarget : TargetRules
{
	public U1908_04_CombatEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "U1908_04_Combat" } );
	}
}
