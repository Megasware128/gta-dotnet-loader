namespace Megasware128.GTA.Abstractions.Game;

public interface IGameEvents
{
    event EventHandler<EventArgs> OnTick;
}
