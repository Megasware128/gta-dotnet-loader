using Megasware128.GTA.Abstractions;
using Megasware128.GTA.Abstractions.Game;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using System.Composition;

namespace SamplePlugin;

[Export(typeof(IPlugin))]
[method: ImportingConstructor]
public class SamplePlugin(IHud hud, IGameUtilities helpers, IMessages messages) : IPlugin
{
    private readonly IHud _hud = hud;
    private readonly IGameUtilities _helpers = helpers;
    private readonly IMessages _messages = messages;

    public async ValueTask InitializeAsync(IServiceProvider services)
    {
        services.GetRequiredService<ILogger<SamplePlugin>>().LogInformation("Hello, World!");

        await Task.Delay(TimeSpan.FromSeconds(5));

        _hud.ShowHelpMessage("Hello, World!");
    }

    public void Tick(float deltaTime)
    {
        _messages.Show($"Player position: {_helpers.FindPlayerPed().Position}", Convert.ToInt32(deltaTime * 1000));
    }
}
