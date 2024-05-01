namespace Megasware128.GTA.Abstractions.Game;

public interface IPed
{
    public float Health { get; set; }
}

public interface IPlayerPed : IPed
{
}
