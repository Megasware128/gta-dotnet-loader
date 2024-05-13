namespace Megasware128.GTA.Abstractions.Game;

public interface IPed : IEntity
{
    public float Health { get; set; }
    public bool IsAimingGun { get; }
    public bool IsInVehicle { get; }
}

public interface IPlayerPed : IPed
{
    public int WantedLevel { get; set; }
    public bool CanStartMission { get; }
}
