using Megasware128.GTA.Abstractions;
using Microsoft.Extensions.Logging;
using Microsoft.VisualStudio.Composition;
using NReco.Logging.File;
using System.Reflection;

namespace Megasware128.GTA.Runtime;

public static class PluginSystem
{
    public static async void Initialize(Assembly entryAssembly)
    {
        var logger = new FileLoggerProvider($"logs/{entryAssembly.GetName().Name}.log").CreateLogger("PluginSystem");

        logger.LogInformation("Initializing plugin system");

        const string pluginPath = "plugins";
        var directory = new DirectoryInfo(pluginPath);
        if (!directory.Exists)
        {
            logger.LogInformation("Creating plugin directory");
            directory.Create();
        }

        logger.LogInformation("Loading plugins");

        var resolver = new Resolver(new PluginLoader(directory));

        var discovery = PartDiscovery.Combine(resolver, new AttributedPartDiscoveryV1(resolver), new AttributedPartDiscovery(resolver));

        var entryParts = await discovery.CreatePartsAsync(entryAssembly);
        var parts = await discovery.CreatePartsAsync(directory.EnumerateFiles("*.dll").Select(file => file.FullName));

        var catalog = ComposableCatalog.Create(resolver).AddParts(entryParts).AddParts(parts).WithCompositionService();

        foreach (var part in catalog.DiscoveredParts.DiscoveryErrors)
        {
            logger.LogError(part, "Error loading plugin {Plugin}", part.AssemblyPath);
        }

        var configuration = CompositionConfiguration.Create(catalog);

        foreach (var error in configuration.CompositionErrors.SelectMany(errors => errors))
        {
            logger.LogError("Error in composition: {Error}", error.Message);
        }

        var factory = configuration.CreateExportProviderFactory();

        var provider = factory.CreateExportProvider();

        var plugins = provider.GetExports<IPlugin>();

        logger.LogInformation("Initializing {PluginCount} plugins", plugins.Count());

        foreach (var plugin in plugins.Select(plugin => plugin.Value))
        {
            plugin.Initialize();
        }

        logger.LogInformation("Plugin system initialized");
    }
}
