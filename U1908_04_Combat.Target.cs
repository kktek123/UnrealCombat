// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class U1908_04_CombatTarget : TargetRules
{
	public U1908_04_CombatTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "U1908_04_Combat" } );
	}
}
