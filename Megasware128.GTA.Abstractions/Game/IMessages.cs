namespace Megasware128.GTA.Abstractions.Game;

public interface IMessages
{
    void Show(string message);
    void Show(string message, int duration);
}
