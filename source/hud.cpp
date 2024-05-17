#include "hud.h"

#pragma unmanaged
#include <CHud.h>

static void addHelpMessage(LPCTSTR message, bool quick, bool permanent) {
#ifdef GTASA
	CHud::SetHelpMessage(message, quick, permanent, false);
#elif defined(GTAVC)
	CHud::SetHelpMessage(message, quick, permanent);
#elif defined(GTA3)
	CHud::SetHelpMessage(const_cast<LPTSTR>(message), quick);
#endif
}

#pragma managed
#include <msclr/marshal.h>

using namespace msclr::interop;

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace Megasware128::GTA::Abstractions::Game;

void Hud::ShowHelpMessage(String^ message, bool quick, bool permanent) {
	marshal_context context;
	addHelpMessage(context.marshal_as<LPCTSTR>(message), quick, permanent);
}
