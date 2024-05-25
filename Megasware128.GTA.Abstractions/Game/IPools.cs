namespace Megasware128.GTA.Abstractions.Game;

public interface IPools
{
    IEnumerable<IPed> Peds { get; }
    IEnumerable<IVehicle> Vehicles { get; }
}
