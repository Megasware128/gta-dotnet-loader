namespace Megasware128.GTA.Abstractions;

public interface IPlugin
{
    ValueTask InitializeAsync(IServiceProvider services);
    void Tick(float deltaTime);
}
