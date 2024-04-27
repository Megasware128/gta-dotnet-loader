#include "plugin.h"

using namespace plugin;

class DotNetLoader {
public:
    DotNetLoader() {
		MessageBox(0, "Hello, World!", "DotNetLoader", MB_OK);
	};
} DotNetLoaderPlugin;
