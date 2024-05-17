#include "hud.h"

#pragma unmanaged
#include <CHud.h>

static void addHelpMessage(const char* message, bool quick, bool permanent) {
#ifdef GTASA
	CHud::SetHelpMessage(message, quick, permanent, false);
#else
	CHud::SetHelpMessage(message, quick, permanent);
#endif // GTASA
}

#pragma managed
#include <msclr/marshal.h>

using namespace msclr::interop;

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace Megasware128::GTA::Abstractions::Game;

void Hud::ShowHelpMessage(String^ message, bool quick, bool permanent) {
	marshal_context context;
	addHelpMessage(context.marshal_as<const char*>(message), quick, permanent);
}
