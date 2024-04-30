using Megasware128.GTA.Abstractions;
using Megasware128.GTA.Abstractions.Game;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using System.Composition;

namespace SamplePlugin;

[Export(typeof(IPlugin))]
[method: ImportingConstructor]
public class SamplePlugin(IHud hud) : IPlugin
{
    private readonly IHud _hud = hud;

    public async void Initialize(IServiceProvider services)
    {
        services.GetRequiredService<ILogger<SamplePlugin>>().LogInformation("Hello, World!");

        await Task.Delay(TimeSpan.FromSeconds(5));

        _hud.ShowHelpMessage("Hello, World!");
    }
}
