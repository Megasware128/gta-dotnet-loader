#include "messages.h"

#pragma unmanaged
#ifndef GTAIV
#include "CMessages.h"
#else
#include "Rage.h"
#include "extensions/ScriptCommands.h"
#endif

static void addMessage(const char* message, int duration) {
#ifndef GTAIV
	CMessages::AddMessageJumpQ(const_cast<char*>(message), duration, 0, false);
#else
	plugin::Command<void, plugin::Commands::PRINT_STRING_WITH_LITERAL_STRING>("STRING", message);
#endif
}

#pragma managed
#include <msclr/marshal.h>

using namespace msclr::interop;

using namespace System;
using namespace Megasware128::GTA::Abstractions::Game;

void Messages::Show(String^ message) {
	Show(message, 5000);
}

void Messages::Show(String^ message, int duration) {
	marshal_context^ context = gcnew marshal_context();
	addMessage(context->marshal_as<const char*>(message), duration);
}
