namespace Megasware128.GTA.Abstractions.Game;

public interface IHud
{
    void ShowHelpMessage(string message, bool quick = false, bool permanent = false);
}
