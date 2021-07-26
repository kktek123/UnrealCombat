// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class U1908_04_Combat : ModuleRules
{
	public U1908_04_Combat(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "NavigationSystem",
            "GameplayTasks",
            "ApexDestruction"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
            "TimeSynth","CableComponent",
        });
    }
}
