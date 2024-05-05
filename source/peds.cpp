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

#ifndef GTAIV
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
	return _ped->m_nPedFlags.bInVehicle;
}

void Ped::IsInVehicle::set(bool value) {
	_ped->m_nPedFlags.bInVehicle = value;
}
#else
bool Ped::IsStanding::get() {
	throw gcnew System::NotImplementedException();
}

void Ped::IsStanding::set(bool value) {
	throw gcnew System::NotImplementedException();
}

bool Ped::IsAimingGun::get() {
	if (_ped->m_WeaponData.m_pTargetEntity)
	{
		return true;
	}

	throw gcnew System::NotImplementedException();
}

void Ped::IsAimingGun::set(bool value) {
	throw gcnew System::NotImplementedException();
}

bool Ped::IsInVehicle::get() {
	return !_ped->m_bNotInVehicle;
}

void Ped::IsInVehicle::set(bool value) {
	_ped->m_bNotInVehicle = !value;
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

