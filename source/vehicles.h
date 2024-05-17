#pragma once
#pragma unmanaged
#include <CVehicle.h>

#pragma managed
#include "entity.h"

private ref class Vehicle : public Entity, public Megasware128::GTA::Abstractions::Game::IVehicle {
private:
    CVehicle* _vehicle;
public:
    Vehicle(CVehicle* vehicle);

    virtual property float Health {
        float get();
        void set(float value);
    }

    virtual property byte PrimaryColor {
        byte get();
        void set(byte value);
    }

    virtual property byte SecondaryColor {
        byte get();
        void set(byte value);
    }

    virtual property bool IsEngineOn {
        bool get();
        void set(bool value);
    }

    virtual property bool IsLocked {
        bool get();
        void set(bool value);
    }
};
