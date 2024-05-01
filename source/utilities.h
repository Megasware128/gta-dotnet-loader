#pragma unmanged
#include "common.h"

static CPlayerPed* findPlayerPed() {
	return FindPlayerPed();
}

static CVehicle* findPlayerVehicle(bool includeRemote) {
	return FindPlayerVehicle(0, includeRemote);
}

#pragma managed
#include "peds.h"
#include "vehicles.h"

using namespace System;
using namespace System::Composition;
using namespace System::Runtime::InteropServices;
using namespace Megasware128::GTA::Abstractions::Game;

[Export(IGameUtilities::typeid)]
public ref class GameUtilities : public IGameUtilities {
public:
	virtual IPlayerPed^ FindPlayerPed() {
		return gcnew PlayerPed(findPlayerPed());
	}

	virtual IVehicle^ FindPlayerVehicle() {
		return gcnew Vehicle(findPlayerVehicle(true));
	}
};