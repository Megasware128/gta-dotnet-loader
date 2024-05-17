#include "messages.h"

#pragma unmanaged
#include <CMessages.h>

static void addMessage(LPCTSTR message, int duration) {
#ifdef GTASA
	CMessages::AddMessageJumpQ(const_cast<LPTSTR>(message), duration, 0, false);
#else
	CMessages::AddMessageJumpQ(const_cast<LPTSTR>(message), duration, 0);
#endif // GTASA
}

#pragma managed
#include <msclr/marshal_cppstd.h>

using namespace msclr::interop;

using namespace System;
using namespace Megasware128::GTA::Abstractions::Game;

void Messages::Show(String^ message) {
	Show(message, 5000);
}

void Messages::Show(String^ message, int duration) {
	marshal_context^ context = gcnew marshal_context();
	addMessage(context->marshal_as<LPCTSTR>(message), duration);
}
