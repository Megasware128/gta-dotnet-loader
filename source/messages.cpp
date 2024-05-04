#include "messages.h"

#pragma unmanaged
#include "CMessages.h"

static void addMessage(char* message, int duration) {
	CMessages::AddMessageJumpQ(message, duration, 0, false);
}

#pragma managed

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace Megasware128::GTA::Abstractions::Game;

void Messages::Show(String^ message) {
	Show(message, 5000);
}

void Messages::Show(String^ message, int duration) {
	IntPtr ptr = Marshal::StringToHGlobalAnsi(message);
	char* str = static_cast<char*>(ptr.ToPointer());
	addMessage(str, duration);
	Marshal::FreeHGlobal(ptr);
}
