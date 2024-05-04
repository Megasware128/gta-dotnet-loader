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
	entity->SetPosn(value.X, value.Y, value.Z);
}

Vector3 Entity::Rotation::get() {
	Vector3 rot{};
	entity->GetOrientation(rot.X, rot.Y, rot.Z);
	return rot;
}

void Entity::Rotation::set(Vector3 value) {
	entity->SetOrientation(value.X, value.Y, value.Z);
}
