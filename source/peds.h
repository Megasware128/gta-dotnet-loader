#pragma once
#pragma unmanaged
#include "CPlayerPed.h"

#pragma managed

using namespace System;
using namespace System::Composition;
using namespace Megasware128::GTA::Abstractions::Game;

private ref class Ped : public IPed {
private:
	CPed* _ped;
public:
	Ped(CPed* ped) {
		_ped = ped;
	}

	virtual property float Health {
		float get() {
			return _ped->m_fHealth;
		}
		void set(float value) {
			_ped->m_fHealth = value;
		}
	}
};

private ref class PlayerPed : public Ped, public IPlayerPed {
private:
	CPlayerPed* _ped;
public:
	PlayerPed(CPlayerPed* ped) : Ped(ped) {
		_ped = ped;
	}
};