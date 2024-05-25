using Megasware128.GTA.Abstractions;
using Megasware128.GTA.Abstractions.Game;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using System.Composition;

namespace SamplePlugin;

[Export(typeof(IPlugin))]
[method: ImportingConstructor]
public class SamplePlugin(IHud hud, IGameUtilities helpers, IMessages messages, IPools pools)
    : IPlugin
{
    private readonly IHud _hud = hud;
    private readonly IGameUtilities _helpers = helpers;
    private readonly IMessages _messages = messages;
    private readonly IPools _pools = pools;

    public async void Initialize(IServiceProvider services)
    {
        services.GetRequiredService<ILogger<SamplePlugin>>().LogInformation("Hello, World!");

        await Task.Delay(TimeSpan.FromSeconds(5));

        _hud.ShowHelpMessage("Hello, World!");

        while (true)
        {
            await Task.Delay(TimeSpan.FromSeconds(10));

            foreach (var vehicle in _pools.Vehicles)
            {
                byte randomColor = (byte)Random.Shared.Next(69);
                vehicle.PrimaryColor = randomColor;
            }
        }
    }
}
