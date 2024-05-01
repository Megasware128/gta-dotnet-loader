#pragma unmanged
#include "common.h"

static CPlayerPed* findPlayerPed() {
	return FindPlayerPed();
}

#pragma managed
#include "peds.h"

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
};