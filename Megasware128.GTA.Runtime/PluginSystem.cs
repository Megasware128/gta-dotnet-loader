using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.DependencyInjection.Extensions;
using Microsoft.Extensions.Hosting;
using Microsoft.VisualStudio.Composition;
using NReco.Logging.File;
using System.Reflection;

namespace Megasware128.GTA.Runtime;

public static class PluginSystem
{
    public static IHost Initialize(Assembly loaderAssembly)
    {
        var host = new HostBuilder()
            .UseContentRoot(Directory.GetCurrentDirectory())
            .ConfigureServices(services =>
            {
                services.AddSingleton<IHostLifetime, NullLifetime>();

                services.TryAddSingleton<IPluginLocator, PluginLocator>();
                services.TryAddSingleton<IAssemblyLoader, PluginLoader>();

                services.AddSingleton<Resolver>();

                services.AddSingleton<AttributedPartDiscoveryV1>();
                services.AddSingleton<AttributedPartDiscovery>();

                services.AddSingleton(provider => PartDiscovery.Combine(provider.GetRequiredService<Resolver>(), provider.GetRequiredService<AttributedPartDiscoveryV1>(), provider.GetRequiredService<AttributedPartDiscovery>()));

                services.Configure<PluginLoaderOptions>(options => options.LoaderAssembly = loaderAssembly);

                services.AddHostedService<PluginService>();
            })
            .ConfigureLogging(logging =>
            {
                logging.AddFile("gta-plugin-runtime.log");
            })
            .Build();

        host.Start();

        return host;
    }

    private sealed class NullLifetime : IHostLifetime
    {
        public Task WaitForStartAsync(CancellationToken cancellationToken) => Task.CompletedTask;

        public Task StopAsync(CancellationToken cancellationToken) => Task.CompletedTask;
    }
}
