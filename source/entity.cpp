#include "entity.h"

#ifdef GTAIV
#define CVector rage::Vector3
#endif

#pragma managed

using namespace System::Numerics;
using namespace Megasware128::GTA::Abstractions::Game;

static Vector3 ToVector3(CVector vec) {
	return Vector3(vec.x, vec.y, vec.z);
}

static CVector ToCVector(Vector3 vec) {
	return CVector(vec.X, vec.Y, vec.Z);
}

Entity::Entity(CEntity* entity) {
	this->entity = entity;
}

Vector3 Entity::Position::get() {
	return ToVector3(entity->GetPosition());
}

void Entity::Position::set(Vector3 value) {
#ifndef GTAIV
	entity->SetPosn(value.X, value.Y, value.Z);
#else
	entity->m_Transform.m_vPosn = ToCVector(value);
#endif
}

Vector3 Entity::Rotation::get() {
#ifndef GTAIV
	Vector3 rot{};
	entity->GetOrientation(rot.X, rot.Y, rot.Z);
	return rot;
#else
	return ToVector3(entity->m_pMatrix->GetRotation());
#endif
}

void Entity::Rotation::set(Vector3 value) {
#ifndef GTAIV
	entity->SetOrientation(value.X, value.Y, value.Z);
#else
	entity->m_pMatrix->SetRotate(ToCVector(value));
#endif
}
