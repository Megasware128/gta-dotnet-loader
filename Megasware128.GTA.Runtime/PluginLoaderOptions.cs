using System.Reflection;

namespace Megasware128.GTA.Runtime;

public class PluginLoaderOptions
{
    public string PluginsPath { get; set; } = "plugins";
    public string PluginSearchPattern { get; set; } = "*.dll";

    public required Assembly LoaderAssembly { get; set; }
}
