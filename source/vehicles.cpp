#include "vehicles.h"

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
    throw gcnew System::NotImplementedException();
}

void Vehicle::IsEngineOn::set(bool value) {
    throw gcnew System::NotImplementedException();
}

bool Vehicle::IsLocked::get() {
    throw gcnew System::NotImplementedException();
}

void Vehicle::IsLocked::set(bool value) {
    throw gcnew System::NotImplementedException();
}
#endif
