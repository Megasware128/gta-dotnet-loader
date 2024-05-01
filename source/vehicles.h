#pragma once
#pragma unmanaged
#include "CVehicle.h"

#pragma managed

using namespace System;
using namespace System::Composition;
using namespace Megasware128::GTA::Abstractions::Game;

private ref class Vehicle : public IVehicle {
private:
    CVehicle* _vehicle;
public:
    Vehicle(CVehicle* vehicle) {
        _vehicle = vehicle;
    }

    virtual property float Health {
        float get() {
            return _vehicle->m_fHealth;
        }
        void set(float value) {
            _vehicle->m_fHealth = value;
        }
    }

    virtual property byte PrimaryColor {
        byte get() {
            return _vehicle->m_nPrimaryColor;
        }
        void set(byte value) {
            _vehicle->m_nPrimaryColor = value;
        }
    }

    virtual property byte SecondaryColor {
        byte get() {
            return _vehicle->m_nSecondaryColor;
        }
        void set(byte value) {
            _vehicle->m_nSecondaryColor = value;
        }
    }

    virtual property bool IsEngineOn {
        bool get() {
            return _vehicle->m_nVehicleFlags.bEngineOn;
        }
        void set(bool value) {
            _vehicle->m_nVehicleFlags.bEngineOn = value;
        }
    }
};