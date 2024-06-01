#include "peds.h"

#pragma managed

using namespace Megasware128::GTA::Abstractions::Game;

Ped::Ped(CPed* ped) : Entity(ped) {
	_ped = ped;
}

float Ped::Health::get() {
	return _ped->m_fHealth;
}

void Ped::Health::set(float value) {
	_ped->m_fHealth = value;
}

bool Ped::IsStanding::get() {
	return _ped->m_nPedFlags.bIsStanding;
}

bool Ped::IsAimingGun::get() {
	return _ped->m_nPedFlags.bIsAimingGun;
}

bool Ped::IsInVehicle::get() {
#ifdef GTASA
	return _ped->m_nPedFlags.bInVehicle;
#else
	return _ped->m_bInVehicle;
#endif // GTASA
}

PlayerPed::PlayerPed(CPlayerPed* ped) : Ped(ped) {
	_ped = ped;
}

int PlayerPed::WantedLevel::get() {
#ifndef GTA3
	return _ped->GetWantedLevel();
#else
	return _ped->m_pWanted->m_nWantedLevel;
#endif
}

void PlayerPed::WantedLevel::set(int value) {
	_ped->SetWantedLevel(value);
}

bool PlayerPed::CanStartMission::get() {
#ifdef GTASA
	return _ped->CanPlayerStartMission();
#else
	return true;
#endif // GTASA
}
