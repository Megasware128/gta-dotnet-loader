namespace Megasware128.GTA.Abstractions.Game;

public interface IPed : IEntity
{
    public float Health { get; set; }
}

public interface IPlayerPed : IPed
{
}
