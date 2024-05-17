#include "messages.h"

#pragma unmanaged
#include "CHud.h"

static void addMessage(const char* message, int duration) {
#ifdef GTASA
	CMessages::AddMessageJumpQ(const_cast<char*>(message), duration, 0, false);
#else
	CHud::SetMessage(message); // TODO: This is not the correct way to do it
#endif // GTASA
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
