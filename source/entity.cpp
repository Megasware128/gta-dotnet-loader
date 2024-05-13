#include "entity.h"

#pragma managed

using namespace System::Numerics;
using namespace Megasware128::GTA::Abstractions::Game;

static Vector3 ToVector3(CVector vec) {
	return Vector3(vec.x, vec.y, vec.z);
}

Entity::Entity(CEntity* entity) {
	this->entity = entity;
}

Vector3 Entity::Position::get() {
	return ToVector3(entity->GetPosition());
}

void Entity::Position::set(Vector3 value) {
#ifdef GTASA
	entity->SetPosn(value.X, value.Y, value.Z);
#else
	entity->SetPosition(value.X, value.Y, value.Z);
#endif
}

Vector3 Entity::Rotation::get() {
	Vector3 rot{};
#ifdef GTASA
	entity->GetOrientation(rot.X, rot.Y, rot.Z);
#else // GTASA
	entity->m_placement.GetOrientation(rot.X, rot.Y, rot.Z);
#endif
	return rot;
}

void Entity::Rotation::set(Vector3 value) {
#ifdef GTASA
	entity->SetOrientation(value.X, value.Y, value.Z);
#else // GTASA
	entity->m_placement.SetOrientation(value.X, value.Y, value.Z);
#endif // GTASA
}
