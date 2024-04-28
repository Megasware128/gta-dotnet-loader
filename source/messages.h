#pragma unmanaged
#include "CMessages.h"

static void addMessage(char* message, int duration) {
	CMessages::AddMessageJumpQ(message, duration, 0, false);
}

#pragma managed

using namespace System;
using namespace System::Composition;
using namespace System::Runtime::InteropServices;
using namespace Megasware128::GTA::Abstractions::Game;

[Export(IMessages::typeid)]
public ref class Messages : public IMessages {
public:
	virtual void Show(String^ message) {
		addMessage((char*)(Marshal::StringToHGlobalAnsi(message)).ToPointer(), 1000);
	}

	virtual void Show(String^ message, int duration) {
		addMessage((char*)(Marshal::StringToHGlobalAnsi(message)).ToPointer(), duration);
	}
};