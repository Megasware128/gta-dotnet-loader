#pragma once
#pragma unmanaged
#include "CEntity.h"

#pragma managed

using namespace System;
using namespace System::Numerics;
using namespace Megasware128::GTA::Abstractions::Game;

static Vector3 ToVector3(CVector vec) {
	return Vector3(vec.x, vec.y, vec.z);
}

ref class Entity : public IEntity
{
private:
	CEntity* entity;
public:
	Entity(CEntity* entity) {
		this->entity = entity;
	}

	virtual property Vector3 Position {
		Vector3 get() {
			return ToVector3(entity->GetPosition());
		}
		void set(Vector3 value) {
			entity->SetPosn(value.X, value.Y, value.Z);
		}
	}

	virtual property Vector3 Rotation {
		Vector3 get() {
			Vector3 rot{};
			entity->GetOrientation(rot.X, rot.Y, rot.Z);
			return rot;
		}
		void set(Vector3 value) {
			entity->SetOrientation(value.X, value.Y, value.Z);
		}
	}
};