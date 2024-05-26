using System.Numerics;

namespace Megasware128.GTA.Abstractions.Game;

public interface IEntity
{
    Vector3 Position { get; set; }
    Vector3 Rotation { get; set; }
}
