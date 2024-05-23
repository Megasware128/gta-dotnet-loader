#pragma once
#pragma unmanaged
#include <CPlayerPed.h>

#pragma managed
#include "entity.h"

ref class Ped : public Entity, public Megasware128::GTA::Abstractions::Game::IPed {
private:
    CPed* _ped;
public:
    Ped(CPed* ped);

    virtual property float Health {
        float get();
        void set(float value);
    }

    virtual property bool IsStanding {
        bool get();
        void set(bool value);
    }

    virtual property bool IsAimingGun {
        bool get();
        void set(bool value);
    }

    virtual property bool IsInVehicle {
        bool get();
        void set(bool value);
    }
};

private ref class PlayerPed : public Ped, public Megasware128::GTA::Abstractions::Game::IPlayerPed {
private:
    CPlayerPed* _ped;
public:
    PlayerPed(CPlayerPed* ped);

    virtual property int WantedLevel {
        int get();
        void set(int value);
    }

    virtual property bool CanStartMission {
        bool get();
    }
};
