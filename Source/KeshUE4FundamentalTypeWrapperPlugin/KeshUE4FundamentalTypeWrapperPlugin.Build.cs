using UnrealBuildTool;

public class KeshUE4FundamentalTypeWrapperPlugin : ModuleRules
{
    public KeshUE4FundamentalTypeWrapperPlugin(TargetInfo Target)
    {
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });
    }
}
