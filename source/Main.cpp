#pragma managed
#include "messages.h"
#include "hud.h"
#include "utilities.h"
#include <msclr/gcroot.h>

using namespace Microsoft::Extensions::Hosting;
using namespace Megasware128::GTA::Runtime;

msclr::gcroot<IHost^> host;

static void LoadDotNet() {
	host = PluginSystem::Initialize(System::Reflection::Assembly::GetExecutingAssembly());
}

#pragma unmanaged
#include <plugin.h>
#include <windows.h>

using namespace plugin;

class DotNetLoader {
public:
	DotNetLoader() {
		Events::initGameEvent += [] {
			LoadDotNet();
			};
	};
};

DotNetLoader* DotNetLoaderPlugin;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DotNetLoaderPlugin = new DotNetLoader();
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
