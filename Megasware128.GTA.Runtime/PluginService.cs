using Megasware128.GTA.Abstractions;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Hosting;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Options;
using Microsoft.VisualStudio.Composition;
using System.Reflection;

namespace Megasware128.GTA.Runtime;

internal class PluginService(IOptions<PluginLoaderOptions> options, Resolver resolver, PartDiscovery discovery, IPluginLocator locator, ILogger<PluginService> logger, IServiceScopeFactory serviceScopeFactory) : BackgroundService
{
    private readonly PluginLoaderOptions _options = options.Value;
    private readonly Resolver _resolver = resolver;
    private readonly PartDiscovery _discovery = discovery;
    private readonly IPluginLocator _locator = locator;
    private readonly ILogger _logger = logger;
    private readonly IServiceScopeFactory _serviceScopeFactory = serviceScopeFactory;

    protected override async Task ExecuteAsync(CancellationToken stoppingToken)
    {
        _logger.LogInformation("Loading plugins...");

        async Task<DiscoveredParts> LoadParts<T>(T source, bool throwOnError = false)
        {
            var parts = source switch
            {
                Assembly assembly => await _discovery.CreatePartsAsync(assembly, stoppingToken),
                IEnumerable<string> paths => await _discovery.CreatePartsAsync(paths, cancellationToken: stoppingToken),
                _ => throw new NotSupportedException()
            };

            foreach (var ex in parts.DiscoveryErrors)
            {
                _logger.LogError(ex, "Error discovering {Assembly} parts", ex.AssemblyPath);
            }

            if (throwOnError)
            {
                parts.ThrowOnErrors();
            }

            foreach (var part in parts.Parts)
            {
                _logger.LogTrace("Discovered part {Part}", part);
            }

            return parts;
        }

        _logger.LogDebug("Loading loader parts from {Assembly}", _options.LoaderAssembly);

        var loaderParts = await LoadParts(_options.LoaderAssembly, true);

        _logger.LogDebug("Loader parts loaded");

        _logger.LogDebug("Loading plugin parts from {Count} plugins", _locator.Plugins.Count());

        var pluginParts = await LoadParts(_locator.Plugins.Select(file => file.FullName), false);

        _logger.LogDebug("{Count} plugin parts loaded", pluginParts.Parts.Count);

        var catalog = ComposableCatalog.Create(_resolver).AddParts(loaderParts).AddParts(pluginParts).WithCompositionService();

        var configuration = CompositionConfiguration.Create(catalog);

        var factory = configuration.CreateExportProviderFactory();

        var provider = factory.CreateExportProvider();

        var plugins = provider.GetExports<IPlugin>();

        foreach (var plugin in plugins.Select(plugin => plugin.Value))
        {
            var scope = _serviceScopeFactory.CreateScope();
            plugin.Initialize(scope.ServiceProvider);
        }
    }
}
