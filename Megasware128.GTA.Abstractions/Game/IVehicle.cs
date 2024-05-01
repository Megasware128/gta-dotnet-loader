namespace Megasware128.GTA.Abstractions.Game;

public interface IVehicle
{
    float Health { get; set; }
    byte PrimaryColor { get; set; }
    byte SecondaryColor { get; set; }
    bool IsEngineOn { get; set; }
    bool IsLocked { get; set; }
}
