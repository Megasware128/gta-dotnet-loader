using Megasware128.GTA.Abstractions;
using Megasware128.GTA.Abstractions.Game;
using System.Composition;

namespace SamplePlugin;

[Export(typeof(IPlugin))]
[method: ImportingConstructor]
public class SamplePlugin(IMessages messages) : IPlugin
{
    private readonly IMessages _messages = messages;

    public async void Initialize()
    {
        await Task.Delay(TimeSpan.FromSeconds(5));

        _messages.Show("Hello, World!", 5000);
    }
}
