#include "vehicles.h"

#pragma managed

using namespace System;
using namespace Megasware128::GTA::Abstractions::Game;

Vehicle::Vehicle(CVehicle* vehicle) : Entity(vehicle) {
    _vehicle = vehicle;
}

float Vehicle::Health::get() {
    return _vehicle->m_fHealth;
}

void Vehicle::Health::set(float value) {
    _vehicle->m_fHealth = value;
}

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
