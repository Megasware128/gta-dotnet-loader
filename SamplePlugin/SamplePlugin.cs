using Megasware128.GTA.Abstractions;
using Megasware128.GTA.Abstractions.Game;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using System.Composition;

namespace SamplePlugin;

[Export(typeof(IPlugin))]
[method: ImportingConstructor]
public class SamplePlugin(IHud hud, IGameUtilities helpers) : IPlugin
{
    private readonly IHud _hud = hud;
    private readonly IGameUtilities _helpers = helpers;

    public async void Initialize(IServiceProvider services)
    {
        services.GetRequiredService<ILogger<SamplePlugin>>().LogInformation("Hello, World!");

        await Task.Delay(TimeSpan.FromSeconds(5));

        _hud.ShowHelpMessage("Hello, World!");

        await Task.Delay(TimeSpan.FromMinutes(1));

        _helpers.FindPlayerPed().Health = 0;
    }
}
