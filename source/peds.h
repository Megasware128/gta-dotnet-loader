#pragma once
#pragma unmanaged
#include "CPlayerPed.h"

#pragma managed
#include "entity.h"

using namespace System;
using namespace System::Composition;
using namespace Megasware128::GTA::Abstractions::Game;

private ref class Ped : public Entity, public IPed {
private:
    CPed* _ped;
public:
    Ped(CPed* ped) : Entity(ped) {
        _ped = ped;
    }

    virtual property float Health {
        float get() {
            return _ped->m_fHealth;
        }
        void set(float value) {
            _ped->m_fHealth = value;
        }
    }

    virtual property bool IsStanding {
        bool get() {
            return _ped->m_nPedFlags.bIsStanding;
        }
        void set(bool value) {
            _ped->m_nPedFlags.bIsStanding = value;
        }
    }

    virtual property bool IsAimingGun {
        bool get() {
            return _ped->m_nPedFlags.bIsAimingGun;
        }
        void set(bool value) {
            _ped->m_nPedFlags.bIsAimingGun = value;
        }
    }

    virtual property bool IsInVehicle {
        bool get() {
            return _ped->m_nPedFlags.bInVehicle;
        }
        void set(bool value) {
            _ped->m_nPedFlags.bInVehicle = value;
        }
    }
};

private ref class PlayerPed : public Ped, public IPlayerPed {
private:
    CPlayerPed* _ped;
public:
    PlayerPed(CPlayerPed* ped) : Ped(ped) {
        _ped = ped;
    }

    virtual property int WantedLevel {
        int get() {
            return _ped->GetWantedLevel();
        }
        void set(int value) {
            _ped->SetWantedLevel(value);
        }
    }

    virtual property bool CanStartMission {
        bool get() {
            return _ped->CanPlayerStartMission();
        }
    }
};