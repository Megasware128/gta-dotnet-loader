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

    public async void Initialize(IServiceProvider services)
    {
        services.GetRequiredService<ILogger<SamplePlugin>>().LogInformation("Hello, World!");

        await Task.Delay(TimeSpan.FromSeconds(5));

        var playerPed = _helpers.FindPlayerPed();

        while (true)
        {
            _messages.Show($"Player position: {playerPed.Position}", 100);

            await Task.Delay(TimeSpan.FromMilliseconds(100));
        }
    }
}
