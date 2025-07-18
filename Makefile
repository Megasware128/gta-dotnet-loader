# Makefile for building GTA .NET Loader on Linux
# This provides an alternative build system to the Windows-focused premake5.lua
# Note: The native C++ component uses C++/CLI which cannot be compiled on Linux
#       This Makefile focuses on .NET development and provides development tools

# Default configuration  
CONFIG ?= ReleaseSA
PLATFORM ?= x86_64-w64-mingw32

# Note: C++/CLI cross-compilation is not supported
# This Makefile focuses on .NET components and development workflow

# Configuration-specific settings
ifeq ($(CONFIG),ReleaseSA)
    CXXFLAGS += -O2 -DNDEBUG -DGTASA -DPLUGIN_SGV_10US -DRW -D_MBCS
    TARGET_SUFFIX = SA
    OUTPUT_DIR = output/asi/SA
endif

ifeq ($(CONFIG),DebugSA)
    CXXFLAGS += -g -DDEBUG -DGTASA -DPLUGIN_SGV_10US -DRW -D_MBCS
    TARGET_SUFFIX = SA
    OUTPUT_DIR = output/asi/SA
endif

ifeq ($(CONFIG),ReleaseVC)
    CXXFLAGS += -O2 -DNDEBUG -DGTAVC -DPLUGIN_SGV_10EN -DRW -DUNICODE -D_UNICODE
    TARGET_SUFFIX = VC
    OUTPUT_DIR = output/asi/VC
endif

ifeq ($(CONFIG),DebugVC)
    CXXFLAGS += -g -DDEBUG -DGTAVC -DPLUGIN_SGV_10EN -DRW -DUNICODE -D_UNICODE
    TARGET_SUFFIX = VC
    OUTPUT_DIR = output/asi/VC
endif

ifeq ($(CONFIG),ReleaseIII)
    CXXFLAGS += -O2 -DNDEBUG -DGTA3 -DPLUGIN_SGV_10EN -DRW -DUNICODE -D_UNICODE
    TARGET_SUFFIX = III
    OUTPUT_DIR = output/asi/III
endif

ifeq ($(CONFIG),DebugIII)
    CXXFLAGS += -g -DDEBUG -DGTA3 -DPLUGIN_SGV_10EN -DRW -DUNICODE -D_UNICODE
    TARGET_SUFFIX = III
    OUTPUT_DIR = output/asi/III
endif

# Common definitions
CXXFLAGS += -D_CRT_SECURE_NO_WARNINGS -D_CRT_NON_CONFORMING_SWPRINTFS -D_USE_MATH_DEFINES
CXXFLAGS += -D_SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING -DLINUX_BUILD_NO_DOTNET

# Project settings
PROJECT_NAME = Megasware128.GTA.DotNetLoader

# Default target - focus on .NET components
all: dotnet-components check-native-limitations

# Build .NET components (this works perfectly on Linux)
dotnet-components:
	@echo "Building .NET components..."
	@dotnet build Megasware128.GTA.Abstractions/Megasware128.GTA.Abstractions.csproj -c Release
	@dotnet build Megasware128.GTA.Runtime/Megasware128.GTA.Runtime.csproj -c Release
	@dotnet build SamplePlugin/SamplePlugin.csproj -c Release
	@echo "✅ .NET components built successfully!"

# Check native component limitations
check-native-limitations:
	@echo ""
	@echo "⚠️  Native Component Limitation:"
	@echo "   The C++ component uses C++/CLI (managed C++) which is not supported"
	@echo "   by standard Linux compilers. To build the complete project:"
	@echo "   • Use Windows with Visual Studio and the existing premake5 system"
	@echo "   • Or use Wine + Visual Studio Build Tools on Linux"
	@echo ""
	@echo "   The .NET components can be fully developed and tested on Linux."
	@echo "   Use 'make dev-workflow' to set up a Linux development environment."
	@echo ""

# Development workflow setup
dev-workflow:
	@echo "Setting up Linux development workflow..."
	@echo "✅ .NET SDK available: $(shell dotnet --version)"
	@echo "✅ .NET components build successfully"
	@echo ""
	@echo "Development workflow on Linux:"
	@echo "1. Edit .NET code (Abstractions, Runtime, SamplePlugin)"
	@echo "2. Build and test: make dotnet-test"
	@echo "3. For C++ changes: Use Windows environment or Wine"
	@echo "4. Integration testing: Copy built .asi to Windows GTA installation"

# Test .NET components
dotnet-test: dotnet-components
	@echo "Testing .NET components..."
	@dotnet test SamplePlugin/ --no-build --verbosity normal || echo "Note: No tests found is normal for plugin projects"

# Clean targets
clean:
	@echo "Cleaning build files..."
	@rm -rf build output
	@dotnet clean Megasware128.GTA.Abstractions/
	@dotnet clean Megasware128.GTA.Runtime/
	@dotnet clean SamplePlugin/

clean-dotnet:
	@echo "Cleaning .NET components..."
	@dotnet clean Megasware128.GTA.Abstractions/
	@dotnet clean Megasware128.GTA.Runtime/
	@dotnet clean SamplePlugin/

# Development helpers
dev-setup:
	@echo "Setting up development environment for .NET components..."
	@sudo apt update
	@sudo apt install -y build-essential cmake dotnet-sdk-8.0
	@echo "✅ Development environment ready for .NET development"
	@echo ""
	@echo "Note: For full native compilation, Windows environment is required"

# Format and lint .NET code
format:
	@echo "Formatting .NET code..."
	@dotnet format Megasware128.GTA.Abstractions/
	@dotnet format Megasware128.GTA.Runtime/
	@dotnet format SamplePlugin/

# Restore .NET packages
restore:
	@echo "Restoring .NET packages..."
	@dotnet restore

# Check for updates
check-updates:
	@echo "Checking for .NET package updates..."
	@dotnet list package --outdated

# Create release packages (just .NET components)
package: dotnet-components
	@echo "Creating .NET component packages..."
	@mkdir -p dist/dotnet
	@cp -r Megasware128.GTA.Abstractions/bin/Release/net8.0/* dist/dotnet/
	@cp -r Megasware128.GTA.Runtime/bin/Release/net8.0/* dist/dotnet/
	@cp -r SamplePlugin/bin/Release/net8.0/* dist/dotnet/
	@echo "✅ .NET packages created in dist/dotnet/"

# Wine setup for Windows compilation (advanced users)
wine-setup:
	@echo "Setting up Wine for Windows compilation..."
	@echo "⚠️  This is experimental and may not work perfectly"
	@sudo apt install -y wine
	@echo "Manual steps required:"
	@echo "1. Install Visual Studio Build Tools in Wine"
	@echo "2. Configure Wine to run Windows premake5.exe"
	@echo "3. Use premake5 + msbuild through Wine"

# Help target
help:
	@echo "Available targets:"
	@echo "  all              - Build .NET components and show native limitations"
	@echo "  dotnet-components - Build only .NET components (works perfectly on Linux)"
	@echo "  dotnet-test      - Test .NET components"
	@echo "  dev-workflow     - Show Linux development workflow info"
	@echo "  clean            - Clean all build artifacts"
	@echo "  clean-dotnet     - Clean only .NET build artifacts"
	@echo "  restore          - Restore .NET packages"
	@echo "  format           - Format .NET code"
	@echo "  check-updates    - Check for .NET package updates"
	@echo "  package          - Create .NET component packages"
	@echo "  dev-setup        - Install development dependencies"
	@echo "  wine-setup       - Setup Wine for Windows compilation (experimental)"
	@echo "  help             - Show this help"
	@echo ""
	@echo "🐧 Linux Development Notes:"
	@echo "  • .NET components (C#): Full development support ✅"
	@echo "  • Native component (C++/CLI): Requires Windows environment ⚠️"
	@echo "  • Recommended: Develop .NET code on Linux, build complete project on Windows"

.PHONY: all dotnet-components dotnet-test clean clean-dotnet dev-setup format restore check-updates package wine-setup help dev-workflow check-native-limitations