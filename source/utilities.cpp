#include "utilities.h"

#pragma unmanaged
#include "common.h"

static CPlayerPed* findPlayerPed() {
	return FindPlayerPed(0);
}

static CVehicle* findPlayerVehicle(bool includeRemote) {
#ifndef GTAIV
	return FindPlayerVehicle(0, includeRemote);
#else
	return FindPlayerVehicle(0);
#endif
}

#pragma managed

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace Megasware128::GTA::Abstractions::Game;

Megasware128::GTA::Abstractions::Game::IPlayerPed^ GameUtilities::FindPlayerPed() {
	return gcnew PlayerPed(findPlayerPed());
}

Megasware128::GTA::Abstractions::Game::IVehicle^ GameUtilities::FindPlayerVehicle() {
	return gcnew Vehicle(findPlayerVehicle(true));
}
