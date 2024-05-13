#include "hud.h"

#pragma unmanaged
#ifndef GTAIV
#include "CHud.h"
#else
#include "Rage.h"
#include "extensions/ScriptCommands.h"
#endif

static void addHelpMessage(const char* message, bool quick, bool permanent) {
#ifndef GTAIV
	CHud::SetHelpMessage(message, quick, permanent, false);
#else
	// TODO: Fix this
	//plugin::Command<void, plugin::Commands::PRINT_HELP_WITH_STRING>("STRING", "Hello World!");
#endif
}

#pragma managed
#include <msclr/marshal.h>

using namespace msclr::interop;

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace Megasware128::GTA::Abstractions::Game;

void Hud::ShowHelpMessage(String^ message, bool quick, bool permanent) {
#ifdef GTAIV
	throw gcnew NotSupportedException("This method is not supported yet.");
#endif // GTAIV

	marshal_context context;
	addHelpMessage(context.marshal_as<const char*>(message), quick, permanent);
}
