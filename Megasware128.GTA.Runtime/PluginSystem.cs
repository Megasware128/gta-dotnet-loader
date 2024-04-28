﻿using Megasware128.GTA.Abstractions;
using Microsoft.VisualStudio.Composition;

namespace Megasware128.GTA.Runtime;

public static class PluginSystem
{
    public static async void Initialize()
    {
        const string pluginPath = "plugins";
        var directory = new DirectoryInfo(pluginPath);
        if (!directory.Exists)
        {
            directory.Create();
        }

        var resolver = new Resolver(new PluginLoader(directory));

        var discovery = PartDiscovery.Combine(resolver, new AttributedPartDiscoveryV1(resolver), new AttributedPartDiscovery(resolver));

        var parts = await discovery.CreatePartsAsync(directory.EnumerateFiles("*.dll").Select(file => file.FullName));

        var catalog = ComposableCatalog.Create(resolver).AddParts(parts).WithCompositionService();

        var configuration = CompositionConfiguration.Create(catalog);

        var factory = configuration.CreateExportProviderFactory();

        var provider = factory.CreateExportProvider();

        var plugins = provider.GetExports<IPlugin>();

        foreach (var plugin in plugins.Select(plugin => plugin.Value))
        {
            plugin.Initialize();
        }
    }
}
