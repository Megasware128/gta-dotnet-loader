#pragma managed

static int RandomNumber() {
    return System::Random::Shared->Next();
}

#pragma unmanaged
#include "plugin.h"
#include <windows.h>

using namespace plugin;

class DotNetLoader {
public:
    DotNetLoader() {
        auto number = RandomNumber();
        MessageBox(0, std::to_string(number).c_str(), "Random Number", 0);
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
