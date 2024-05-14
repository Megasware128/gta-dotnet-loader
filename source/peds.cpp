#include "peds.h"
#include "extensions/ScriptCommands.h"
#include <vehicles.h>

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

#ifndef GTAIV
bool Ped::IsAimingGun::get() {
	return _ped->m_nPedFlags.bIsAimingGun;
}

bool Ped::IsInVehicle::get() {
	return _ped->m_nPedFlags.bInVehicle;
}

IVehicle^ Ped::Vehicle::get() {
	return gcnew ::Vehicle(_ped->m_pVehicle);
}

void Ped::Vehicle::set(IVehicle^ value) {
	_ped->m_pVehicle = ((::Vehicle^)value)->_vehicle;
}
#else
bool Ped::IsAimingGun::get() {
	if (_ped->m_WeaponData.m_pTargetEntity) // Hacky, maybe remove this functionality entirely
	{
		return true;
	}

	return false;
}

bool Ped::IsInVehicle::get() {
	return !_ped->m_bNotInVehicle;
}

IVehicle^ Ped::Vehicle::get() {
	return gcnew ::Vehicle(_ped->m_pVehicle);
}

void Ped::Vehicle::set(IVehicle^ value) {
	_ped->m_pVehicle = ((::Vehicle^)value)->_vehicle;
}
#endif

PlayerPed::PlayerPed(CPlayerPed* ped) : Ped(ped) {
	_ped = ped;
}

#ifndef GTAIV
int PlayerPed::WantedLevel::get() {
	return _ped->GetWantedLevel();
}

void PlayerPed::WantedLevel::set(int value) {
	_ped->SetWantedLevel(value);
}

bool PlayerPed::CanStartMission::get() {
	return _ped->CanPlayerStartMission();
}
#else
int PlayerPed::WantedLevel::get() {
	return _ped->m_bWantedByPolice;
}

void PlayerPed::WantedLevel::set(int value) {
	_ped->m_bWantedByPolice = value;
}

bool PlayerPed::CanStartMission::get() {
	return _ped->CanStartMission();
}
#endif

