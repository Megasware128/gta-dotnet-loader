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

void Ped::IsStanding::set(bool value) {
    _ped->m_nPedFlags.bIsStanding = value;
}

bool Ped::IsAimingGun::get() {
    return _ped->m_nPedFlags.bIsAimingGun;
}

void Ped::IsAimingGun::set(bool value) {
    _ped->m_nPedFlags.bIsAimingGun = value;
}

bool Ped::IsInVehicle::get() {
#ifdef GTASA
    return _ped->m_nPedFlags.bInVehicle;
#else
	return _ped->m_bInVehicle;
#endif // GTASA
}

void Ped::IsInVehicle::set(bool value) {
#ifdef GTASA
    _ped->m_nPedFlags.bInVehicle = value;
#else
	_ped->m_bInVehicle = value;
#endif // GTASA
}

PlayerPed::PlayerPed(CPlayerPed* ped) : Ped(ped) {
    _ped = ped;
}

int PlayerPed::WantedLevel::get() {
    return _ped->GetWantedLevel();
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
