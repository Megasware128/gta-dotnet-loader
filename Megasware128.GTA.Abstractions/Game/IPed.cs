namespace Megasware128.GTA.Abstractions.Game;

public interface IPed : IEntity
{
    public float Health { get; set; }
    public bool IsStanding { get; set; }
    public bool IsAimingGun { get; set; }
    public bool IsInVehicle { get; set; }
}

public interface IPlayerPed : IPed
{
    public int WantedLevel { get; set; }
    public bool CanStartMission { get; }
}
