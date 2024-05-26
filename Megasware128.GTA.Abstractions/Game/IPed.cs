namespace Megasware128.GTA.Abstractions.Game;

public interface IPed : IEntity
{
    float Health { get; set; }
    bool IsStanding { get; set; }
    bool IsAimingGun { get; set; }
    bool IsInVehicle { get; set; }
}

public interface IPlayerPed : IPed
{
    int WantedLevel { get; set; }
    bool CanStartMission { get; }
}
