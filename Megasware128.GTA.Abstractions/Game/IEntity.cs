using System.Numerics;

namespace Megasware128.GTA.Abstractions.Game;

public interface IEntity
{
    public Vector3 Position { get; set; }
    public Vector3 Rotation { get; set; }
}
