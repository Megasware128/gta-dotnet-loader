#include "vehicles.h"
#include "extensions/ScriptCommands.h"

#pragma managed

using namespace System;
using namespace Megasware128::GTA::Abstractions::Game;

Vehicle::Vehicle(CVehicle* vehicle) : Entity(vehicle) {
    _vehicle = vehicle;
}

float Vehicle::Health::get() {
#ifndef GTAIV
    return _vehicle->m_fHealth;
#else
    return _vehicle->m_fLife;
#endif

}

void Vehicle::Health::set(float value) {
#ifndef GTAIV
    _vehicle->m_fHealth = value;
#else
    _vehicle->SetHealth(value, 0);
#endif
}

#ifndef GTAIV
byte Vehicle::PrimaryColor::get() {
    return _vehicle->m_nPrimaryColor;
}

void Vehicle::PrimaryColor::set(byte value) {
    _vehicle->m_nPrimaryColor = value;
}

byte Vehicle::SecondaryColor::get() {
    return _vehicle->m_nSecondaryColor;
}

void Vehicle::SecondaryColor::set(byte value) {
    _vehicle->m_nSecondaryColor = value;
}

bool Vehicle::IsEngineOn::get() {
    return _vehicle->m_nVehicleFlags.bEngineOn;
}

void Vehicle::IsEngineOn::set(bool value) {
    _vehicle->m_nVehicleFlags.bEngineOn = value;
}

bool Vehicle::IsLocked::get() {
    return _vehicle->m_nVehicleFlags.bIsLocked;
}

void Vehicle::IsLocked::set(bool value) {
    _vehicle->m_nVehicleFlags.bIsLocked = value;
}
#else
byte Vehicle::PrimaryColor::get() {
    return _vehicle->m_nColor1;
}

void Vehicle::PrimaryColor::set(byte value) {
    _vehicle->m_nColor1 = value;
}

byte Vehicle::SecondaryColor::get() {
    return _vehicle->m_nColor2;
}

void Vehicle::SecondaryColor::set(byte value) {
    _vehicle->m_nColor2 = value;
}

bool Vehicle::IsEngineOn::get() {
	return plugin::Command<float, plugin::Commands::GET_VEHICLE_ENGINE_REVS>(_vehicle) > 0.0f;
}

void Vehicle::IsEngineOn::set(bool value) {
	plugin::Command<void, plugin::Commands::SET_CAR_ENGINE_ON>(_vehicle, value);
}

bool Vehicle::IsLocked::get() {
	return plugin::Command<bool, plugin::Commands::GET_CAR_DOOR_LOCK_STATUS>(_vehicle) > 1;
}

void Vehicle::IsLocked::set(bool value) {
	plugin::Command<void, plugin::Commands::LOCK_CAR_DOORS>(_vehicle, value ? 2 : 1);
}
#endif
