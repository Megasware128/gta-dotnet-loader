#pragma once
#pragma unmanaged
#include "CEntity.h"

#pragma managed

ref class Entity : public Megasware128::GTA::Abstractions::Game::IEntity
{
private:
	CEntity* entity;
public:
	Entity(CEntity* entity);

	virtual property System::Numerics::Vector3 Position {
		System::Numerics::Vector3 get();
		void set(System::Numerics::Vector3 value);
	}

	virtual property System::Numerics::Vector3 Rotation {
		System::Numerics::Vector3 get();
		void set(System::Numerics::Vector3 value);
	}
};
