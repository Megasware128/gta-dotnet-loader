#pragma once
#include "peds.h"
#include "vehicles.h"

[System::Composition::Export(Megasware128::GTA::Abstractions::Game::IGameUtilities::typeid)]
public ref class GameUtilities : public Megasware128::GTA::Abstractions::Game::IGameUtilities {
public:
	virtual Megasware128::GTA::Abstractions::Game::IPlayerPed^ FindPlayerPed();
	virtual Megasware128::GTA::Abstractions::Game::IVehicle^ FindPlayerVehicle();
};
