#pragma unmanged
#include "CHud.h"

static void addHelpMessage(char* message, bool quick, bool permanent) {
	CHud::SetHelpMessage(message, quick, permanent, false);
}

#pragma managed

using namespace System;
using namespace System::Composition;
using namespace System::Runtime::InteropServices;
using namespace Megasware128::GTA::Abstractions::Game;

[Export(IHud::typeid)]
public ref class Hud : public IHud {
public:
	virtual void ShowHelpMessage(String^ message, bool quick, bool permanent) {
		addHelpMessage((char*)(Marshal::StringToHGlobalAnsi(message)).ToPointer(), quick, permanent);
	}
};