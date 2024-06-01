namespace Megasware128.GTA.Abstractions.Game;

public interface IPed : IEntity
{
    float Health { get; set; }
    bool IsStanding { get; }
    bool IsAimingGun { get; }
    bool IsInVehicle { get; }
}

public interface IPlayerPed : IPed
{
    int WantedLevel { get; set; }
    bool CanStartMission { get; }
}
